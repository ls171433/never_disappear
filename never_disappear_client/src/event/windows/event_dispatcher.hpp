#pragma once

#include "os/os_defines.hpp"
#if defined(NDC_OS_WINDOWS)

#include <map>
#include <mutex>
#include <vector>

#include <windows.h>

#include "event/event_dispatcher_base.hpp"

namespace never_disappear_client
{

class windows_event_base;

class windows_event_dispatcher final : public event_dispatcher_base<windows_event_base>
{
public:
    windows_event_dispatcher();
    ~windows_event_dispatcher();

    virtual bool run() override;
    virtual void stop() override;

protected:
    virtual void internal_add_event(event_base_type&) override;
    virtual void internal_remove_event(event_base_type&) override;

private:
    HANDLE m_update_event = INVALID_HANDLE_VALUE;
    bool m_stop_mark = false;

    std::vector<HANDLE> m_handles;
    std::map<HANDLE, windows_event_base*> m_handle_events;
    std::mutex m_event_mutex;

#if defined(NDC_TEST)
public:
    int m_test_update_event_count = 0;
#endif
};

using os_event_dispatcher = windows_event_dispatcher;

} // namespace never_disappear_client

#endif // defined(NDC_OS_WINDOWS)
