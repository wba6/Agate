#include "TaskPool.h"
#include "ProcessConcurrency.h"

namespace Agate {

std::once_flag TaskPool::initializationFlag{};
std::unique_ptr<Agate::TaskPool> TaskPool::instance = nullptr;

TaskPool::TaskPool(unsigned int threadCount) {

    // Workers must all be initialized before any workers are started
    workers.resize(threadCount);
    for (std::size_t i = 0; i < threadCount; ++i) {
        workers[i] = std::make_unique<TaskWorker>(i, std::span(workers));
    }
    for (std::size_t i = 0; i < workers.size(); ++i) {
        workers[i]->Start();
    }
}

TaskPool::~TaskPool() {
    shutdown.store(true);
    for (std::size_t i = 0; i < workers.size(); ++i) {
        if (workers[i]) {
            workers[i]->RequestStop();
        }
    }
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
