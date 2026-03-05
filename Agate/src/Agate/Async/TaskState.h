/**
 * @brief Include file for asynchronous task shared state
 */

#ifndef AGATE_TASKSTATE_H
#define AGATE_TASKSTATE_H

#include <atomic>
#include <concepts>
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>
#include <type_traits>


namespace Agate {

/**
 * @brief Descriptor for the current status of a task
 */
enum class TaskStatus : std::uint32_t {
    Ready               = 0,                        /*!< Task is in a queue and awaiting a worker to run it */
    Working             = 1 << 0,                   /*!< Task is being run by a worker thread */
    Done                = 1 << 1,                   /*!< Task has finished running and its result is ready for extraction */
    CancelRequested     = 1 << 2,                   /*!< Task has received a cancellation request */
    Cancelled           = 1 << 3,                   /*!< Task has stopped running due to being cancelled */
    Error               = 1 << 4,                   /*!< Task has stopped running due encountering an error state */
    Terminal            = Error | Cancelled | Done  /*!< Task is in a terminal state - The task pool has discarded it */
};

constexpr inline TaskStatus operator|(TaskStatus left, TaskStatus right) {
    return static_cast<TaskStatus>(
        static_cast<std::uint32_t>(left) |
        static_cast<std::uint32_t>(right)
    );
}

constexpr inline TaskStatus operator&(TaskStatus left, TaskStatus right) {
    return static_cast<TaskStatus>(
        static_cast<std::uint32_t>(left) &
        static_cast<std::uint32_t>(right)
    );
}

/**
 * @brief Type erasing wrapper for task callbacks so that anything
 *        that can be invoked using the qualified result type can
 *        be contained in a qualified task state
 * 
 * @tparam ResultType Type returned by the task (and therefore, the
 *         type this callback takes as a parameter)
 */
template<typename ResultType>
class TaskCallback {
public:
    /**
     * @brief Virtual destructor for subclasses
     */
    virtual ~TaskCallback() = default;

    /**
     * @brief Invokes the callback with the result of the task
     */
    virtual void Run(ResultType& result) = 0;
};

/**
 * @brief A callback specialized for a specific function type
 * 
 * @tparam ResultType Type returned by the task (and therefore, the
 *         type this callback takes as a parameter)
 * 
 * @tparam FuncType Type of the callback invocable
 */
template<typename ResultType, typename FuncType>
    requires std::invocable<FuncType, ResultType>
class QualifiedCallback : public TaskCallback<ResultType> {
private:
    FuncType callback;
public:

    /**
     * @brief Forwarding constructor
     * 
     * @param callback Invocable to 
     */
    QualifiedCallback(FuncType&& callback)
        : callback(std::forward<FuncType>(callback)) {}
    
    /**
     * @brief Invokes the callback with the result of the task
     */
    virtual void Run(ResultType& result) override {
        callback(result);
    }
};

/**
 * @brief Shared state wrapper for qualified tasks
 * 
 * Contains a pointer to the result type along with
 * concurrency primitives to allow the task pool and
 * main thread to safely access the status and result
 * of a qualified task
 * 
 * @tparam ResultType Type returned by the task
 */
template<typename ResultType>
struct QualifiedTaskState {

    std::optional<ResultType> result;
    std::unique_ptr<TaskCallback<ResultType>> callback;

    std::mutex mutex;
    std::condition_variable condition;
    std::atomic<TaskStatus> status;
};

} // namespace Agate

#endif
