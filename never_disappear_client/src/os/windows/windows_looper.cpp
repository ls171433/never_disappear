#include "windows_looper.hpp"

#include <windows.h>

namespace never_disappear_client {

windows_looper::windows_looper() {
    m_update_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (m_update_event == INVALID_HANDLE_VALUE) {}
    m_events.push_back(m_update_event);
#if !defined(NDC_TEST)
    m_event_callbacks[m_update_event] = []{};
#else
    m_event_callbacks[m_update_event] = [this]{
        ++m_test_update_event_count;
    };
#endif
}

windows_looper::~windows_looper() {
    CloseHandle(m_update_event);
}

void windows_looper::run() {
    m_stop_mark = false;
    ResetEvent(m_update_event);

    while (true)
    {
        std::vector<os_event> events;
        {
            std::lock_guard<std::mutex> lock(m_event_mutex);
            events = m_events;
        }

        DWORD wait_result = WaitForMultipleObjectsEx(events.size(), events.data(), FALSE, INFINITE, FALSE);
        if (wait_result == WAIT_FAILED)
        {
            break;
        }

        if (m_stop_mark)
        {
            break;
        }

        std::size_t index = wait_result - WAIT_OBJECT_0;
        const os_event& event = events[index];

        event_callback callback;
        auto it = m_event_callbacks.find(event);
        if (it != m_event_callbacks.end())
        {
            callback = it->second;
        }
        callback();
    }
}

void windows_looper::stop() {
    m_stop_mark = true;
    SetEvent(m_update_event);
}

void windows_looper::add_event(const os_event& event, const std::function<void()>& callback)
{
    {
        std::lock_guard<std::mutex> lock(m_event_mutex);
        m_events.erase(std::remove(m_events.begin(), m_events.end(), event), m_events.end());
        m_events.push_back(event);
        m_event_callbacks[event] = callback;
    }

    SetEvent(m_update_event);
}

void windows_looper::remove_event(const os_event& event)
{
    {
        std::lock_guard<std::mutex> lock(m_event_mutex);
        m_events.erase(std::remove(m_events.begin(), m_events.end(), event), m_events.end());
        m_event_callbacks.erase(event);
    }

    SetEvent(m_update_event);
}

} // namespace never_disappear_client
