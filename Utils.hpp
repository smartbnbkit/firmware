#ifndef UTILS_HPP
#define UTILS_HPP

extern "C" {
#   include "user_interface.h"
}

void startTimer(ETSTimer *timer, void(*callback)(), int interval, bool repeating = true) {
    os_timer_disarm(timer);
    os_timer_setfn(timer, (os_timer_func_t *)callback, NULL);
    os_timer_arm(timer, interval, repeating);
}

#endif
