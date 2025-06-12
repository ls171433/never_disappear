#pragma once

#include "os/os_defines.hpp"
#if defined(NDC_OS_WINDOWS)

#include <functional>

#include <windows.h>

#include "event/windows/event_base.hpp"

namespace never_disappear_client
{

class windows_simple_event final : public windows_event_base
{
public:
    using callback_type = std::function<void()>;

public:
    windows_simple_event();
    ~windows_simple_event();

    virtual void trigger();
    virtual bool is_triggered();

    virtual void call_callback();

    virtual void set_callback(const callback_type& callback);

protected:
    virtual void internal_call_callback();

private:
    bool m_triggered;
    callback_type m_callback;
};

using os_simple_event = windows_simple_event;

} // namespace never_disappear_client

#endif // defined(NDC_OS_WINDOWS)
