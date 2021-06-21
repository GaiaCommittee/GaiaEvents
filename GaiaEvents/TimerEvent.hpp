#pragma once

#include "Event.hpp"

#include <thread>
#include <future>
#include <atomic>
#include <chrono>

namespace Gaia::Events
{
    /**
     * @brief Timer event will be automatically triggered after given time.
     * @details
     *  A TimerEvent will create and manage a background thread.
     *  Though the timer thread will sleep during the most of the time and normally
     *  will not consume much CPU resource, it is still not recommended to create
     *  many TimerEvents.
     */
    class TimerEvent : public Event<void>
    {
    protected:
        std::future<void> TimerToken;
        std::atomic_bool TimerFlag {false};

    public:
        /// Default constructor.
        TimerEvent() = default;
        /// Constructor with a initial interval time.
        explicit TimerEvent(std::chrono::steady_clock::duration interval_time) : IntervalTime(interval_time)
        {}

        /// Destructor which will auto stop the timer.
        ~TimerEvent() override;

        /// The interval time between event handlers executed.
        std::atomic<std::chrono::steady_clock::duration> IntervalTime {std::chrono::seconds(1)};

        /// Start the background timer thread.
        void Start();
        /// Require and wait for the timer to stop.
        void Stop();
    };
}