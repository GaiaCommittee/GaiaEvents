#pragma once

#include <functional>
#include <type_traits>

namespace Gaia::Events
{
    /**
     * @brief The base class of all Functor-like classes.
     * @tparam ExecutableType The type of the object to execute.
     * @details
     *  Types of parameters for functions can not be void, thus Functor without parameters should be specialized.
     *  This base class is extracted to provide basic constructors and operators.
     */
    template <typename ExecutableType>
    class FunctorBase
    {
    protected:
        /// Executable object to perform the real action.
        ExecutableType ExecutableInstance;

        /// Clear the ExecutableInstance.
        virtual void Clear() = 0;

    public:
        /**
         * @brief Check whether this functor is empty or not.
         * @retval true Functor is empty, Execute(...) will return directly.
         * @retval false Functor is not empty, Execute(...) will perform the operation.
         */
        virtual bool IsEmpty() = 0;

        /// Default constructor.
        FunctorBase() = default;
        /// Move constructor.
        FunctorBase(FunctorBase&& target) noexcept : ExecutableInstance(std::move(target.ExecutableInstance))
        {}
        /// Copy constructor.
        FunctorBase(const FunctorBase& target) : ExecutableInstance(target.ExecutableInstance)
        {}
        /// Initializer constructor.
        explicit FunctorBase(ExecutableType operation) : ExecutableInstance(std::move(operation))
        {}

        /// Explicit cast to the std::function<void(...)> object.
        explicit operator ExecutableType()
        {
            return ExecutableInstance;
        }
        /// Assign a std::function to it.
        FunctorBase& operator=(ExecutableType operation)
        {
            ExecutableInstance = std::move(operation);
            return *this;
        }
        /// Assign a Functor to it.
        FunctorBase& operator=(FunctorBase const& functor)
        {
            ExecutableInstance = functor.ExecutableInstance;
            return *this;
        }
        /**
         * @brief Boolean converter.
         * @retval true FunctorBase is not empty and able to perform action.
         * @retval false FunctorBase is empty will do noting when it's invoked.
         */
        explicit operator bool()
        {
            return !IsEmpty();
        }
    };

    /**
     * @brief Functor represents a function object which can be executed.
     * @tparam ArgumentTypes Optional arguments for invoking the function object.
     * @details
     *  A Functor always returns void.
     */
    template <typename... ArgumentTypes>
    class Functor : public FunctorBase<std::function<void(ArgumentTypes...)>>
    {
    protected:
        using FunctorBaseType = FunctorBase<std::function<void(ArgumentTypes...)>>;

        /// Clear the lambda function.
        void Clear() override
        {
            FunctorBaseType::ExecutableInstance = std::function<void(ArgumentTypes...)>();
        }

    public:
        using FunctorBase<std::function<void(ArgumentTypes...)>>::FunctorBase;

        /**
         * @brief Check whether this functor is empty or not.
         * @retval true Functor is empty, Execute(...) will return directly.
         * @retval false Functor is not empty, Execute(...) will perform the operation.
         */
        bool IsEmpty() override
        {
            return !FunctorBaseType::ExecutableInstance.operator bool();
        }

        /// Execute the operation if it's not empty.
        virtual void Execute(ArgumentTypes... arguments)
        {
            if (!IsEmpty())
            {
                FunctorBaseType::ExecutableInstance(arguments...);
            }
        }

        /// Execute the operation if it's not empty.
        void operator()(ArgumentTypes... arguments)
        {
            Execute(arguments...);
        }
    };

    /**
     * @brief A specialization template Functor without parameters.
     */
    template<>
    class Functor<void> : public FunctorBase<std::function<void()>>
    {
    protected:
        using FunctorBaseType = FunctorBase<std::function<void()>>;

        /// Clear the lambda function.
        void Clear() override
        {
            FunctorBaseType::ExecutableInstance = std::function<void()>();
        }

    public:
        using FunctorBase<std::function<void()>>::FunctorBase;

        /**
         * @brief Check whether this functor is empty or not.
         * @retval true Functor is empty, Execute(...) will return directly.
         * @retval false Functor is not empty, Execute(...) will perform the operation.
         */
        bool IsEmpty() override
        {
            return !FunctorBaseType::ExecutableInstance.operator bool();
        }

        /// Execute the operation if it's not empty.
        virtual void Execute()
        {
            if (!IsEmpty())
            {
                FunctorBaseType::ExecutableInstance();
            }
        }

        /// Execute the operation if it's not empty.
        void operator()()
        {
            Execute();
        }
    };
}