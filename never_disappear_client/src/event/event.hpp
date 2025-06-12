#pragma once

#include "config.hpp"
#include "os/os_defines.hpp"

#include "event_dispatcher_base.hpp"

#if defined(NDC_OS_WINDOWS)
#    include "windows/event_dispatcher.hpp"
#    include "windows/simple_event.hpp"
#endif

namespace never_disappear_client
{

#if defined(USE_OS_EVENT)
using event_dispatcher = os_event_dispatcher;
using simple_event = os_simple_event;
#endif

} // namespace never_disappear_client
