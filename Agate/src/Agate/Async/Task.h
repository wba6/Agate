/**
 * @brief Include file for the Task and QualifiedTask classes
 */

#ifndef AGATE_TASK_H
#define AGATE_TASK_H

#include <concepts>
#include <type_traits>

namespace Agate {

/**
 * @brief Type erasing wrapper for tasks so that all tasks can
 *        be placed in the task queue
 */
class Task {
public:

    /**
     * @brief Virtual destructor for subclasses
     */
    virtual ~Task() = default;

    /**
     * @brief Runs the task
     */
    virtual void Run() = 0;

    /**
     * @brief Cancels the task
     */
    virtual void Cancel() = 0;
};

/**
 * @brief A task specialized for a specific function type
 * 
 * @tparam FuncType Type of the invocable that runs the task
 */
template<typename FuncType, typename CancelType>
    requires std::invocable<FuncType> && std::invocable<CancelType>
class QualifiedTask : public Task {
private:
    FuncType taskFn;
    CancelType cancelFn;
public:

    /**
     * @brief Forwarding constructor
     */
    QualifiedTask(FuncType&& task, CancelType&& cancel)
        : taskFn(std::forward<FuncType>(task)), cancelFn(std::forward<CancelType>(cancel)) {}

    /**
     * @brief Runs the task
     */
    virtual void Run() override {
        taskFn();
    }

    /**
     * @brief Cancels the task
     */
    virtual void Cancel() override {
        cancelFn();
    }
};

} // namespace Agate

#endif
