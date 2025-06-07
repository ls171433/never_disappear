#pragma once

#include <map>
#include <mutex>
#include <vector>

#include <windows.h>

#include "../base/looper_base.hpp"

namespace never_disappear_client {

class windows_looper final : public looper_base {
public:
    windows_looper();
    ~windows_looper();

    void run() override;
    void stop() override;

    void add_event(const os_event& event, const event_callback& callback) override;
    void remove_event(const os_event& event) override;

private:
    os_event m_update_event = INVALID_HANDLE_VALUE;
    bool m_stop_mark = false;
    std::vector<os_event> m_events;
    std::map<os_event, std::function<void()>> m_event_callbacks;
    std::mutex m_event_mutex;

#if defined(NDC_TEST)
public:
    int m_test_update_event_count = 0;
#endif
};

} // namespace never_disappear_client
