#include "os/os_looper.hpp"

int main()
{
    never_disappear_client::os_looper main_looper;
    main_looper.run();
    return 0;
}
