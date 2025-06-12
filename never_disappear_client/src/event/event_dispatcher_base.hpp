#pragma once

#include <atomic>
#include <functional>
#include <list>
#include <mutex>

namespace never_disappear_client
{

template<class event_base_type_template>
class event_dispatcher_base
{
public:
    using event_base_type = event_base_type_template;
    using callback_type = std::function<void()>;

public:
    virtual ~event_dispatcher_base() = default;

    virtual bool run() = 0;
    virtual void stop() = 0;
    virtual bool running() const
    {
        return m_running;
    }

    virtual void add_event(event_base_type& event)
    {
        std::lock_guard<std::mutex> guard{m_event_list_mutex};
        internal_add_event(event);
    }
    virtual void remove_event(event_base_type& event)
    {
        std::lock_guard<std::mutex> guard{m_event_list_mutex};
        internal_remove_event(event);
    }
    virtual bool has_event(event_base_type& event) const
    {
        std::lock_guard<std::mutex> guard{m_event_list_mutex};
        return internal_has_event(event);
    }

    virtual void set_enter_callback(const callback_type& callback)
    {
        m_enter_callback = callback;
    }
    virtual void set_exit_callback(const callback_type& callback)
    {
        m_exit_callback = callback;
    }
    virtual void set_idle_callback(const callback_type& callback)
    {
        m_idle_callback = callback;
    }

protected:
    virtual bool internal_set_running()
    {
        bool expected_running = false;
        return m_running.compare_exchange_strong(expected_running, true);
    }
    virtual void internal_reset_running()
    {
        m_running = false;
    }

    virtual void internal_add_event(event_base_type& event)
    {
        m_event_list.push_back(&event);
    }
    virtual void internal_remove_event(event_base_type& event)
    {
        m_event_list.remove(&event);
    }
    virtual bool internal_has_event(event_base_type& event) const
    {
        return !(std::find(m_event_list.begin(), m_event_list.end(), &event) == m_event_list.end());
    }

    virtual void internal_call_enter_callback()
    {
        if (m_enter_callback)
        {
            m_enter_callback();
        }
    }
    virtual void internal_call_exit_callback()
    {
        if (m_exit_callback)
        {
            m_exit_callback();
        }
    }
    virtual void internal_call_idle_callback()
    {
        if (m_idle_callback)
        {
            m_idle_callback();
        }
    }

protected:
    std::atomic_bool m_running = false;

    std::list<event_base_type*> m_event_list;
    mutable std::mutex m_event_list_mutex;

    callback_type m_enter_callback;
    callback_type m_exit_callback;
    callback_type m_idle_callback;
};

} // namespace never_disappear_client
