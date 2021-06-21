#include <gtest/gtest.h>
#include "../GaiaEvents/GaiaEvents.hpp"
#include <iostream>

using namespace Gaia::Events;

TEST(FunctorTest, VoidParameter)
{
    auto functor = Functor<void>([]{
      std::cout << "Functor executed." << std::endl;
    });

    for(int index = 3; index > 0; --index)
    {
        functor.Execute();
    }

    ASSERT_FALSE(functor.IsEmpty());
}

TEST(FunctorTest, WithParameter)
{
    auto functor = Functor<int>([](int index){
        std::cout << "Functor executed. Index:" << index << std::endl;
    });

    for(int index = 3; index > 0; --index)
    {
        functor.Execute(index);
    }

    ASSERT_FALSE(functor.IsEmpty());
}

TEST(FunctorTest, DisposableFunctor)
{
    auto functor = DisposableFunctor<int>([](int index){
        std::cout << "Functor executed. Index:" << index << std::endl;
    });

    ASSERT_FALSE(functor.IsEmpty());

    functor(1);
    functor(2);
    functor(3);

    ASSERT_TRUE(functor.IsEmpty());
}

TEST(FunctorTest, DisposableFunctorAsFunctor)
{
    auto disposable_functor = DisposableFunctor<int>([](int index){
        std::cout << "Functor executed. Index:" << index << std::endl;
    });

    Functor<int>& functor = disposable_functor;
    functor(1);
    functor(2);
    functor(3);

    ASSERT_TRUE(functor.IsEmpty());
}