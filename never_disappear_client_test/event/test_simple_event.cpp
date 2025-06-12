#include <atomic>
#include <thread>

#include <gtest/gtest.h>

#include "event/event.hpp"

#include <iostream>

using namespace never_disappear_client;
using namespace std;

TEST(test_simple_event, common)
{
    event_dispatcher main_event_dispatcher;

    simple_event event;
    event.set_callback([&]
    {
        cout << "in event callback" << endl;
        main_event_dispatcher.stop();
    });
    main_event_dispatcher.add_event(event);

    main_event_dispatcher.set_enter_callback([&]
    {
        cout << "in enter callback" << endl;
        event.trigger();
    });
    main_event_dispatcher.set_exit_callback([&]
    {
        cout << "in exit callback" << endl;
    });

    main_event_dispatcher.run();
}
