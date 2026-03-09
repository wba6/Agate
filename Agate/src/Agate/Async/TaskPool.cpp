#include "TaskPool.h"
#include "ProcessConcurrency.h"

namespace Agate {

std::once_flag TaskPool::initializationFlag{};
std::unique_ptr<Agate::TaskPool> TaskPool::instance = nullptr;

TaskPool::TaskPool(unsigned int threadCount) {
    for (std::size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back([this]() -> void {

            while (true) {
                std::unique_ptr<Task> currentTask;

                // Wait until a task is ready, then take it from the queue and do it
                {
                    std::unique_lock lock(this->queueLock);
                    this->queueCondition.wait(lock, [this]() -> bool {
                        return this->shutdown.load() || !(this->taskQueue.empty());
                    });

                    // Shutdown - First worker to hit this will flush the queue
                    if (this->shutdown.load()) {
                        while (!this->taskQueue.empty()) {
                            currentTask = std::move(this->taskQueue.front());
                            this->taskQueue.pop();
                            currentTask->Run();
                        }
                        return;
                    }

                    currentTask = std::move(this->taskQueue.front());
                    this->taskQueue.pop();
                }

                currentTask->Run();
            }
        });
    }
}

TaskPool::~TaskPool() {
    shutdown.store(true);
    queueCondition.notify_all();
}

void TaskPool::Initialize() {

    std::call_once(initializationFlag, []() -> void {

        unsigned int threadCount = ProcessConcurrency();
        if (threadCount <= 2U) {
            threadCount = 1;
        } else {
            threadCount -= 2U;
        }
        instance.reset(new TaskPool(threadCount));
    });
}

} // namespace Agate
