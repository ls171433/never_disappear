#pragma once

#include "os_defines.hpp"

#if defined(NDC_OS_WINDOWS)
#    include "windows/windows_looper.hpp"
#endif

namespace never_disappear_client {

#if defined(NDC_OS_WINDOWS)
using os_looper = windows_looper;
#endif

} // namespace never_disappear_client
