#include "os/os_defines.hpp"
#if defined(NDC_OS_WINDOWS)

#include "event_dispatcher.hpp"

#include <windows.h>

#include "event/windows/event_base.hpp"

namespace never_disappear_client
{

windows_event_dispatcher::windows_event_dispatcher()
{
    m_update_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (m_update_event == INVALID_HANDLE_VALUE)
    {
        // TODO: throw
    }

    m_handles.push_back(m_update_event);
#if defined(NDC_TEST)
#endif
}

windows_event_dispatcher::~windows_event_dispatcher()
{
    CloseHandle(m_update_event);
}

bool windows_event_dispatcher::run()
{
    if (!internal_set_running())
    {
        return false;
    }

    m_stop_mark = false;
    ResetEvent(m_update_event);

    internal_call_enter_callback();

    while (true)
    {
        std::vector<HANDLE> handles;
        {
            std::lock_guard<std::mutex> lock(m_event_mutex);
            handles = m_handles;
        }

        DWORD wait_result = WaitForMultipleObjectsEx(handles.size(), handles.data(), FALSE, INFINITE, FALSE);
        if (wait_result == WAIT_FAILED)
        {
            break;
        }

        std::size_t index = wait_result - WAIT_OBJECT_0;
        HANDLE handle = handles[index];

        auto it = m_handle_events.find(handle);
        if (it != m_handle_events.end())
        {
            event_base_type* event = it->second;
            event->call_callback();
        }

        if (m_stop_mark)
        {
            break;
        }
    }

    internal_call_exit_callback();
    internal_reset_running();

    return true;
}

void windows_event_dispatcher::stop()
{
    m_stop_mark = true;
    SetEvent(m_update_event);
}

void windows_event_dispatcher::internal_add_event(event_base_type& event)
{
    event_dispatcher_base::internal_add_event(event);
    m_handles.push_back(event.internal_get_handle());
    m_handle_events[event.internal_get_handle()] = &event;
}

void windows_event_dispatcher::internal_remove_event(event_base_type& event)
{
    event_dispatcher_base::internal_remove_event(event);
    m_handles.erase(std::remove(m_handles.begin(), m_handles.end(), event.internal_get_handle()), m_handles.end());
    m_handle_events.erase(event.internal_get_handle());
}

} // namespace never_disappear_client

#endif // defined(NDC_OS_WINDOWS)
