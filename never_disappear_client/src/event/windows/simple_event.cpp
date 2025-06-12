#include "os/os_defines.hpp"
#if defined(NDC_OS_WINDOWS)

#include "simple_event.hpp"

#include <windows.h>

namespace never_disappear_client
{

windows_simple_event::windows_simple_event()
{
    HANDLE handle = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (handle == INVALID_HANDLE_VALUE)
    {
        // TODO: throw
    }

    internal_set_handle(handle);
}

windows_simple_event::~windows_simple_event()
{
    CloseHandle(internal_get_handle());
}

void windows_simple_event::trigger()
{
    SetEvent(internal_get_handle());
    m_triggered = true;
}

bool windows_simple_event::is_triggered()
{
    return m_triggered;
}

void windows_simple_event::call_callback()
{
    m_triggered = false;
    ResetEvent(internal_get_handle());
    internal_call_callback();
}

void windows_simple_event::set_callback(const callback_type& callback)
{
    m_callback = callback;
}

void windows_simple_event::internal_call_callback()
{
    if (m_callback)
    {
        m_callback();
    }
}

} // namespace never_disappear_client

#endif // defined(NDC_OS_WINDOWS)
