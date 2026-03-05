/**
 * @brief Include file for the Task and QualifiedTask classes
 */

#ifndef AGATE_TASK_H
#define AGATE_TASK_H

#include <concepts>
#include <type_traits>

namespace Agate {

/**
 * @brief Type erasing wrappper for tasks so that all tasks can
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
};

/**
 * @brief A task specialized for a specific function type
 * 
 * @tparam FuncType Type of the invocable that runs the task
 */
template<typename FuncType>
    requires std::invocable<FuncType>
class QualifiedTask : public Task {
private:
    FuncType taskFn;
public:

    /**
     * @brief Forwarding constructor
     */
    QualifiedTask(FuncType&& task)
        : taskFn(std::forward<FuncType>(task)) {}

    /**
     * @brief Runs the task
     */
    virtual void Run() override {
        taskFn();
    }
};

} // namespace Agate

#endif
