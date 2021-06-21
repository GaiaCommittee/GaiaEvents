#pragma once

#include "Event.hpp"

namespace Gaia::Events
{
    /**
     * @brief DestructionEvent will be automatically triggered during its destruction.
     */
    class DestructionEvent : public Event<void>
    {
    public:
        /// Trigger the event when destruct.
        ~DestructionEvent() override;
    };
}