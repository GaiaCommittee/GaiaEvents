#include "TimerEvent.hpp"

namespace Gaia::Events
{
    /// Destructor which will automatically stop the timer.
    TimerEvent::~TimerEvent()
    {
        Stop();
    }

    /// Start the background timer thread.
    void TimerEvent::Start()
    {
        if (TimerToken.valid()) return;

        TimerFlag = true;
        TimerToken = std::async(std::launch::async, [this](){
            while (this->TimerFlag.load())
            {
                std::this_thread::sleep_for(this->IntervalTime.load());
                this->Trigger();
            }
        });
    }

    /// Require and wait for the timer to stop.
    void TimerEvent::Stop()
    {
        TimerFlag = false;
        if (TimerToken.valid())
        {
            TimerToken.get();
        }
    }
}
