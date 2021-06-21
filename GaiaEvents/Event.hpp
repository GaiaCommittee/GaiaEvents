#pragma once

#include "DisposableFunctor.hpp"

#include <list>
#include <shared_mutex>
#include <tbb/tbb.h>
#include <memory>

namespace Gaia::Events
{
    /**
     * @brief Base class for all Event-like classes.
     * @tparam ArgumentTypes The types of arguments for the event handlers.
     * @details
     *  Types of arguments of functions can not be void, thus Event without parameters must be specialized.
     *  This base class is extracted to provide basic functions and operators.
     */
    template<typename... ArgumentTypes>
    class EventBase
    {
    public:
        /// Event handlers are functors with the same parameters structure.
        using Handler = Functor<ArgumentTypes...>;

    protected:
        /// Registered handlers.
        std::list<std::unique_ptr<Handler>> Handlers;
        /// Mutex to protect handlers.
        std::shared_mutex HandlersMutex;

        /// Remove the handler pointed by the given iterator.
        void Remove(typename std::list<std::unique_ptr<Handler>>::iterator iterator)
        {
            Handlers.erase(iterator);
        }

    public:
        /// Make destructors virtual for derived classes.
        virtual ~EventBase() = default;

        /**
         * @brief Add the handler to the handlers list.
         * @param handler The handler to add.
         * @return The Functor to remove the added handler. Notice that this handler can only be called once.
         */
        template<typename HandlerType, typename = typename std::enable_if_t<std::is_base_of_v<Handler, HandlerType>>>
        DisposableFunctor<void> Add(HandlerType handler)
        {
            std::unique_lock lock(HandlersMutex);
            auto finder = Handlers.insert(Handlers.end(), std::unique_ptr<Handler>(new HandlerType(handler)));
            return DisposableFunctor<void>([this, finder](){
                this->Remove(finder);
            });
        }
    };

    /**
     * @brief Event is a Functor container which can execute all event handlers concurrently.
     * @tparam ArgumentTypes Types of arguments to pass.
     */
    template<typename... ArgumentTypes>
    class Event : public EventBase<ArgumentTypes...>
    {
    protected:
        using EventBaseType = EventBase<ArgumentTypes...>;

    public:
        /// Invoke all event handlers concurrently.
        void Trigger(ArgumentTypes... arguments)
        {
            std::shared_lock lock(EventBaseType::HandlersMutex);
            tbb::parallel_for_each(EventBaseType::Handlers, [arguments...](
                    std::unique_ptr<typename EventBaseType::Handler>& handler){
                (*handler)(arguments...);
            });
        }
    };

    /**
     * @brief Event is a Functor container which can execute all event handlers concurrently.
     * @tparam ArgumentTypes Types of arguments to pass.
     */
    template<>
    class Event<void> : public EventBase<void>
    {
    protected:
        using EventBaseType = EventBase<void>;

    public:
        /// Invoke all event handlers concurrently.
        void Trigger()
        {
            std::shared_lock lock(EventBaseType::HandlersMutex);
            tbb::parallel_for_each(EventBaseType::Handlers, [](
                    std::unique_ptr<typename EventBaseType::Handler>& handler){
                (*handler)();
            });
        }
    };
}