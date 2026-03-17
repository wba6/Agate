/**
 * @brief Include file for the TaskWorker class
 */

#ifndef AGATE_TASKWORKER_H
#define AGATE_TASKWORKER_H

#include "Task.h"
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <span>
#include <thread>

namespace Agate {

class TaskWorker {
private:
    unsigned int m_id;
    std::span<std::unique_ptr<TaskWorker>> m_allWorkers;
    std::deque<std::unique_ptr<Task>> m_taskQueue;
    std::mutex m_workerLock;
    std::condition_variable_any m_workerCondition;
    std::jthread m_worker;
public:

    /**
     * @brief Constructor - Initializes with an ID and reference to all
     *        workers, then spins up the worker thread
     * 
     * @param id ID for this worker. Used to prevent self-stealing
     * @param allWorkers Non-owning reference to all available workers for
     *                   work stealing
     */
    TaskWorker(unsigned int id, std::span<std::unique_ptr<TaskWorker>> allWorkers);

    /**
     * @brief Launches the worker thread. Should only be called after all
     *        workers have been initialized
     */
    void Start();

    /**
     * @brief Pushes a task to this worker's queue and notifies the worker
     * 
     * @param task Task to push to this worker's queue
     */
    void Push(std::unique_ptr<Task> task);

    /**
     * @brief Notify this worker that work has been received
     */
    void Notify();

    /**
     * @brief Requests this worker to stop its thread and cancel any remaining
     *        work
     */
    void RequestStop();
private:

    /**
     * @brief Runner for the worker thread
     */
    void Run(std::stop_token stopToken);

    /**
     * @brief Attempts to steal work from another worker
     */
    std::unique_ptr<Task> AttemptSteal();

    /**
     * @brief Extracts stealable work from this worker's queue, if available
     */
    std::unique_ptr<Task> ExtractStolenWork();
};

} // namespace Agate

#endif
