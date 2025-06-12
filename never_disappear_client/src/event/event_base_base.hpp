#pragma once

namespace never_disappear_client
{

class event_base_base
{
public:
    virtual ~event_base_base() = default;

    virtual void trigger() = 0;
    virtual bool is_triggered() = 0;

    virtual void call_callback() = 0;
};

} // namespace never_disappear_client
