#include "TaskWorker.h"
#include <random>

namespace {
    constexpr unsigned int STEAL_ATTEMPTS = 3U;
}

namespace Agate {

TaskWorker::TaskWorker(unsigned int id, std::span<std::unique_ptr<TaskWorker>> allWorkers)
    : m_id(id), m_allWorkers(allWorkers) {

}

void TaskWorker::Start() {
    m_worker = std::jthread([this](std::stop_token stopToken) {
        Run(stopToken);
    });
}

void TaskWorker::Push(std::unique_ptr<Task> task) {

    {
        std::scoped_lock lock(m_workerLock);
        m_taskQueue.push_front(std::move(task));
    }
    m_workerCondition.notify_one();
}

void TaskWorker::Notify() {
    m_workerCondition.notify_one();
}

void TaskWorker::RequestStop() {
    m_worker.request_stop();
}

void TaskWorker::Run(std::stop_token stopToken) {

    while (!stopToken.stop_requested()) {
        std::unique_ptr<Task> currentTask;
        {
            std::unique_lock lock(m_workerLock);

            if (!m_taskQueue.empty()) {

                // Local work
                currentTask = std::move(m_taskQueue.front());
                m_taskQueue.pop_front();
            } else {

                // No local work found
                lock.unlock();
                for (unsigned int i = 0; i < STEAL_ATTEMPTS; ++i) {
                    currentTask = AttemptSteal();
                    if (currentTask) {
                        break;
                    }
                }

                // No work found
                if (!currentTask) {
                    lock.lock();
                    m_workerCondition.wait(lock, stopToken, [this]() -> bool {
                        return !m_taskQueue.empty();
                    });
                }
            }
        }

        // Work found
        if (currentTask) {
            currentTask->Run();
        }
    }

    // Shutdown
    while (true) {
        std::unique_ptr<Task> currentTask;
        {
            std::unique_lock lock(m_workerLock);
            if (m_taskQueue.empty()) {

                return;
            }
            currentTask = std::move(m_taskQueue.front());
            m_taskQueue.pop_front();
        }
        if (currentTask) {
            currentTask->Run();
        }
    }
}

std::unique_ptr<Task> TaskWorker::AttemptSteal() {

    // No workers to steal from
    if (m_allWorkers.size() <= 1) {
        return nullptr;
    }

    static thread_local std::mt19937 generator{ std::random_device{}() };
    unsigned int victim = std::uniform_int_distribution<unsigned int>{ 0, static_cast<unsigned int>(m_allWorkers.size() - 1) }(generator);
    while (victim == m_id) {
        victim = std::uniform_int_distribution<unsigned int>{ 0, static_cast<unsigned int>(m_allWorkers.size() - 1) }(generator);
    }

    return m_allWorkers[victim]->ExtractStolenWork();
}

std::unique_ptr<Task> TaskWorker::ExtractStolenWork() {

    std::unique_lock<std::mutex> lock(m_workerLock, std::try_to_lock);
    if (!lock.owns_lock() || m_taskQueue.empty()) {
        return nullptr;
    }

    std::unique_ptr<Task> stolenWork = std::move(m_taskQueue.back());
    m_taskQueue.pop_back();
    return stolenWork;
}

} // namespace Agate
