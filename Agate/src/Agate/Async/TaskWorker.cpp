#include "TaskWorker.h"
#include <limits>
#include <random>

namespace {
    constexpr unsigned int STEAL_ATTEMPTS = 3U;
}

namespace Agate {

TaskWorker::TaskWorker(unsigned int id, std::span<std::unique_ptr<TaskWorker>> allWorkers)
    : id(id), allWorkers(allWorkers) {

}

void TaskWorker::Start() {
    worker = std::jthread(&TaskWorker::Run, this);
}

void TaskWorker::Push(std::unique_ptr<Task> task) {

    {
        std::scoped_lock lock(workerLock);
        taskQueue.push_front(std::move(task));
    }
    workerCondition.notify_one();
}

void TaskWorker::Notify() {
    workerCondition.notify_one();
}

void TaskWorker::RequestStop() {
    worker.request_stop();
}

void TaskWorker::Run(std::stop_token stopToken) {

    while (!stopToken.stop_requested()) {
        std::unique_ptr<Task> currentTask;
        {
            std::unique_lock lock(workerLock);

            // Find work
            if (taskQueue.empty()) {
                lock.unlock();
                for (unsigned int i = 0; i < STEAL_ATTEMPTS; ++i) {
                    currentTask = AttemptSteal();
                    if (currentTask) {
                        break;
                    }
                }
            } else {
                currentTask = std::move(taskQueue.front());
                taskQueue.pop_front();
            }

            // No work available
            if (!currentTask) {
                lock.lock();
                workerCondition.wait(lock, stopToken, [this]() -> bool {
                    return !taskQueue.empty();
                });
                continue;
            }
        }
        if (currentTask) {
            currentTask->Run();
        }
    }

    // Shutdown
    while (true) {
        std::unique_ptr<Task> currentTask;
        {
            std::unique_lock lock(workerLock);
            if (taskQueue.empty()) {

                return;
            }
            currentTask = std::move(taskQueue.front());
            taskQueue.pop_front();
        }
        if (currentTask) {
            currentTask->Run();
        }
    }
}

std::unique_ptr<Task> TaskWorker::AttemptSteal() {

    // No workers to steal from
    if (allWorkers.size() <= 1) {
        return nullptr;
    }

    static thread_local std::mt19937 generator{ std::random_device{}() };
    unsigned int victim = std::uniform_int_distribution<unsigned int>{ 0, static_cast<unsigned int>(allWorkers.size() - 1) }(generator);
    while (victim == id) {
        victim = std::uniform_int_distribution<unsigned int>{ 0, static_cast<unsigned int>(allWorkers.size() - 1) }(generator);
    }

    return allWorkers[victim]->ExtractStolenWork();
}

std::unique_ptr<Task> TaskWorker::ExtractStolenWork() {

    std::unique_lock<std::mutex> lock(workerLock, std::try_to_lock);
    if (!lock.owns_lock() || taskQueue.empty()) {
        return nullptr;
    }

    std::unique_ptr<Task> stolenWork = std::move(taskQueue.back());
    taskQueue.pop_back();
    return stolenWork;
}

} // namespace Agate
