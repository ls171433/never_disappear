#pragma once

#if defined(_WIN32)
#    define NDC_OS_WINDOWS
#elif defined(__linux__)
#    define NDC_OS_LINUX
#elif defined(__APPLE__)
#    define NDC_OS_MACOS
#else
#    define NDC_OS_UNKNOWN
#endif
