#pragma once

#include <functional>

#include "../os_types.hpp"

namespace never_disappear_client {

using event_callback = std::function<void()>;

class looper_base {
public:
    virtual ~looper_base() = default;

    virtual void run() = 0;
    virtual void stop() = 0;

    virtual void add_event(const os_event& event, const event_callback& callback) = 0;
    virtual void remove_event(const os_event& event) = 0;
};

} // namespace never_disappear_client
