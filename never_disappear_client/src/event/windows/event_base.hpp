#pragma once

#include "os/os_defines.hpp"
#if defined(NDC_OS_WINDOWS)

#include <windows.h>

#include "event/event_base_base.hpp"

namespace never_disappear_client
{

class windows_event_dispatcher;

class windows_event_base : public event_base_base
{
protected:
    virtual void internal_set_handle(HANDLE handle)
    {
        m_handle = handle;
    }
    virtual HANDLE internal_get_handle() const
    {
        return m_handle;
    }

protected:
    HANDLE m_handle;

    friend class windows_event_dispatcher;
};

using os_event_base = windows_event_base;

} // namespace never_disappear_client

#endif // defined(NDC_OS_WINDOWS)
