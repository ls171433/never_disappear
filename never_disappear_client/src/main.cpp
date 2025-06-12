#include "event/event.hpp"

int main()
{
    never_disappear_client::event_dispatcher main_event_dispatcher;
    main_event_dispatcher.set_enter_callback([&]{main_event_dispatcher.stop();});
    main_event_dispatcher.run();
    return 0;
}
