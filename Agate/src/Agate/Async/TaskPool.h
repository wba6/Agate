/**
 * @brief Include file for the task pool
 * 
 * Interface and wrapper for dispatching and handling the
 * cleanup of asynchronous tasks
 */

#ifndef AGATE_TASKPOOL_H
#define AGATE_TASKPOOL_H

#include "Agate/Core/Logger.h"
#include "Task.h"
#include "TaskState.h"
#include <concepts>
#include <memory>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <vector>

namespace Agate {

/**
 * @brief Handle for tracking a task and eventually either extracting
 *        its result or assigning a callback to be executed with the
 *        result
 * 
 * @tparam ResultType Type returned by the task
 */
template<typename ResultType>
class TaskHandle {
private:
    std::shared_ptr<QualifiedTaskState<ResultType>> sharedState;
public:

    TaskHandle(std::shared_ptr<QualifiedTaskState<ResultType>> state = nullptr);

    /**
     * @brief Assigns a callback to be executed upon task completion
     * 
     * @note If this method is called on a completed task, the callback
     *       is immediately called
     * 
     * @param callback Callback to pass task result to
     * 
     * @return Reference to this handle for call chaining
     */
    template<typename FuncType>
    TaskHandle<ResultType>& Then(FuncType&& callback);

    /**
     * @brief Blocks execution until the task for this handle is in a
     *        terminal state
     * 
     * Terminal states are `Done`, `Error`, and `Cancelled`
     * 
     * @return Reference to this handle for call chaining
     */
    TaskHandle<ResultType>& Wait();

    /**
     * @brief Attempts to extract the result from the task for
     *        this handle. Throws if the result is invalid
     * 
     * @return Result of the completed task
     */
    ResultType Get();

    /**
     * @brief Cancels the task. If the task is currently running, it is stopped
     *        and set to a cancelled status. Otherwise, the task is set to a
     *        cancelled status
     */
    void Cancel();

    /**
     * @brief Queries the current status of this handle's task
     * 
     * @return Current task status
     */
    inline TaskStatus Status() const;
};

// Note: Definitions must be outside of the class for MSVC builds

template<typename ResultType>
TaskHandle<ResultType>::TaskHandle(std::shared_ptr<QualifiedTaskState<ResultType>> state)
    : sharedState(state) {}

template<typename ResultType>
template<typename FuncType>
TaskHandle<ResultType>& TaskHandle<ResultType>::Then(FuncType&& callback) {

    std::scoped_lock lock(sharedState->mutex);
    bool statusDone = static_cast<std::uint32_t>(sharedState->status.load() & TaskStatus::Done) == static_cast<std::uint32_t>(TaskStatus::Done);
    if (sharedState->result.has_value() && statusDone) {
        callback(*(sharedState->result));

        return *this;
    }
    auto callbackPtr = std::make_unique<QualifiedCallback<ResultType, FuncType>>(std::forward<FuncType>(callback));
    sharedState->callback = std::move(callbackPtr);

    return *this;
}


template<typename ResultType>
TaskHandle<ResultType>& TaskHandle<ResultType>::Wait() {

    std::unique_lock lock(sharedState->mutex);
    sharedState->condition.wait(lock, [this]() -> bool {
        bool statusTerminal = static_cast<std::uint32_t>(sharedState->status.load() & TaskStatus::Terminal) != static_cast<std::uint32_t>(0);
        return statusTerminal;
    });

    return *this;
}

template<typename ResultType>
ResultType TaskHandle<ResultType>::Get() {

    // Critical error: Invalid access attempt
    if (!sharedState->result.has_value()) {
        PRINTCRIT("Attempted to call `TaskHandle::Get` with an invalid result");
        throw std::runtime_error("Invalid std::optional access attempt");
    }

    ResultType result = std::move(*(sharedState->result));
    sharedState->result.reset();
    return result;
}

template<typename ResultType>
void TaskHandle<ResultType>::Cancel() {
    PRINTWARN("TaskHandle::Cancel not yet implemented");
}

template<typename ResultType>
inline TaskStatus TaskHandle<ResultType>::Status() const {
    return sharedState->status.load();
}

class TaskPool {
private:

    static std::once_flag initializationFlag;
    static std::unique_ptr<TaskPool> instance;

    std::mutex queueLock;
    std::condition_variable queueCondition;
    std::queue<std::unique_ptr<Task>> taskQueue;

    std::atomic<bool> shutdown = false;
    std::vector<std::jthread> workers;

    /**
     * @brief Singleton constructor - initializes worker threads
     */
    TaskPool(unsigned int threadCount);

public:

    /**
     * @brief Destructor - shuts down worker threads and flushes
     *        pending tasks
     */
    ~TaskPool();

    /**
     * @brief Delete copy constructor for singleton
     */
    TaskPool(const TaskPool&) = delete;

    /**
     * @brief Delete copy assignment for singleton
     */
    TaskPool& operator=(const TaskPool&) = delete;

    /**
     * @brief Initializes the singleton instance of the task pool
     * 
     * @note This method should be called only once at startup and
     *       must be called before enqueueing any tasks
     */
    static void Initialize();

    /**
     * @brief Submits a task to the task pool
     * 
     * @tparam TaskFunc Type of the invocable task
     * @tparam Args Types of the arguments to be passed to the invocable task
     * 
     * @param task Task to submit
     * @param args Arguments to bind to the task (if applicable)
     * 
     * @return Handle linked to the task for cancellation, extraction, or continuation
     */
    template<typename TaskFunc, typename... Args>
        requires std::invocable<TaskFunc, Args...>
    static TaskHandle<std::invoke_result_t<std::decay_t<TaskFunc>, std::decay_t<Args>...>> 
    Enqueue(TaskFunc&& task, Args&&... args) {

        using ResultType = std::invoke_result_t<std::decay_t<TaskFunc>, std::decay_t<Args>...>;

        std::shared_ptr<QualifiedTaskState<ResultType>> state = std::make_shared<QualifiedTaskState<ResultType>>();
        TaskHandle<ResultType> handle{ state };

        // Wrap the task with logic to safely store its result in the handle's state
        auto boundTask = [
            task = std::forward<TaskFunc>(task),
            arguments = std::make_tuple(std::forward<Args>(args)...)
        ]() mutable -> ResultType {
            return std::apply(task, arguments);
        };
        auto wrappedTask = [
            state,
            task = std::move(boundTask)
        ]() mutable {

            // Task cancelled before running
            if ((state->status.load() & TaskStatus::CancelRequested) == TaskStatus::CancelRequested) {
                state->status.store(TaskStatus::Cancelled);
                state->condition.notify_all();

                return;
            }

            try {

                state->status.store(TaskStatus::Working);
                ResultType result = task();

                // Safely store result
                {
                    std::scoped_lock lock(state->mutex);
                    state->result = std::move(result);
                    state->status.store(TaskStatus::Done);
                    if (state->callback) {
                        state->callback->Run(*(state->result));
                    }
                }
                state->condition.notify_all();

            } catch (const std::exception& exception) {
                {
                    std::scoped_lock lock(state->mutex);
                    state->status.store(TaskStatus::Error);
                }
                state->condition.notify_all();
            }
        };

        // Package and enqueue task, then alert workers
        std::unique_ptr<Task> packedTask = std::make_unique<QualifiedTask<decltype(wrappedTask)>>(std::move(wrappedTask));
        {
            std::scoped_lock lock(instance->queueLock);
            instance->taskQueue.push(std::move(packedTask));
        }
        instance->queueCondition.notify_one();

        return handle;
    }
};
} // namespace Agate

#endif
