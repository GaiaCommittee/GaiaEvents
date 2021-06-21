#include "DestructionEvent.hpp"

namespace Gaia::Events
{
    /// Trigger all event handlers before its destruction.
    DestructionEvent::~DestructionEvent()
    {
        Trigger();
    }
}