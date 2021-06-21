#include <gtest/gtest.h>
#include "../GaiaEvents/GaiaEvents.hpp"
#include <iostream>
#include <memory>

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

TEST(EventTest, RemoveHandler)
{
    Event<void> test_event;

    auto remover1 = test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 1" << std::endl;
    }));
    auto remove2 = test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 2" << std::endl;
    }));
    auto remove3 = test_event.Add(Functor<void>([]{
        std::cout << "Event handler executed. 3" << std::endl;
    }));

    test_event.Trigger();

    remove2();

    test_event.Trigger();

    remove2();
    ASSERT_TRUE(remove2.IsEmpty());

    test_event.Trigger();
}

TEST(EventTest, RemoveHandlerWithParameter)
{
    Event<int> test_event;

    auto remover1 = test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));
    auto remover2 = test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));
    auto remover3 = test_event.Add(Functor<int>([](int index){
        std::cout << "Event handler executed." << index << std::endl;
    }));

    test_event.Trigger(1);

    remover2();

    test_event.Trigger(2);

    remover2();
    ASSERT_TRUE(remover2.IsEmpty());

    test_event.Trigger(3);
}

TEST(EventTest, AutoRemove)
{
    auto destruction_event = std::make_unique<DestructionEvent>();
    Event<void> test_event;
    destruction_event->Add(test_event.Add(Functor<void>([]{
        std::cout << "Event Handler executed. 1" << std::endl;
    })));

    test_event.Trigger();
    destruction_event.reset();
    test_event.Trigger();
}