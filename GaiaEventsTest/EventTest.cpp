#include <gtest/gtest.h>
#include "../GaiaEvents/GaiaEvents.hpp"
#include <iostream>

using namespace Gaia::Events;

TEST(EventTest, VoidParameter)
{
    Event<void> test_event;

    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 1" << std::endl;
    }));
    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 2" << std::endl;
    }));
    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 3" << std::endl;
    }));

    test_event.Trigger();
}

TEST(EventTest, WithParameter)
{
    Event<int> test_event;

    test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));
    test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));
    test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));

    test_event.Trigger(3);
}

TEST(EventTest, DestructionEvent)
{
    DestructionEvent test_event;

    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed." << std::endl;
    }));
    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed." << std::endl;
    }));
    test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed." << std::endl;
    }));
}