#pragma once

#include "os_defines.hpp"

#if defined(NDC_OS_WINDOWS)
#    include <windows.h>
#endif

namespace never_disappear_client {

#if defined(NDC_OS_WINDOWS)
using os_event = HANDLE;
#endif

} // namespace never_disappear_client
