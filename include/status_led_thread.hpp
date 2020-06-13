#ifndef _STATUS_LED_THREAD_HPP
#define _STATUS_LED_THREAD_HPP

#include "Arduino.h"
#include "ChRt.h"
#include "StripManagement.hpp"
#include "col_enum.h"

extern void start_status_led_thread(void);
extern void status_signal_once(status_led_col colour);
extern void status_change_flash(status_led_col colour);

#endif 