#pragma once

#include "Functor.hpp"

namespace Gaia::Events
{
    /**
     * @brief This kinds of functor will be empty once it's executed.
     * @tparam ArgumentTypes Types of arguments to pass.
     */
    template <typename... ArgumentTypes>
    class DisposableFunctor : public Functor<ArgumentTypes...>
    {
    protected:
        using FunctorType = Functor<ArgumentTypes...>;

    public:
        using Functor<ArgumentTypes...>::Functor;

        /**
         * @brief Execute and then clear the lambda operation.
         * @param arguments Arguments for the lambda operation.
         * @details This functor will be empty after this operation.
         */
        void Execute(ArgumentTypes... arguments) override
        {
            if (!FunctorType::IsEmpty())
            {
                FunctorType::Execute(arguments...);
            }
            FunctorType::Clear();
        }
    };

    /**
     * @brief This kinds of functor will be empty once it's executed.
     * @tparam ArgumentTypes Types of arguments to pass.
     */
    template <>
    class DisposableFunctor<void> : public Functor<void>
    {
    protected:
        using FunctorType = Functor<void>;

    public:
        using FunctorType::Functor;

        /**
         * @brief Execute and then clear the lambda operation.
         * @details This functor will be empty after this operation.
         */
        void Execute() override
        {
            if (!FunctorType::IsEmpty())
            {
                FunctorType::Execute();
            }
            FunctorType::Clear();
        }
    };
}