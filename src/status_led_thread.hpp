#ifndef _STATUS_LED_THREAD_HPP
#define _STATUS_LED_THREAD_HPP

#include "Arduino.h"
#include "ChRt.h"
#include "StripManagement.hpp"

enum status_led_col{
  RGB_COL_RED, 
  RGB_COL_GREEN, 
  RGB_COL_BLUE, 
  RGB_COL_WHITE, 
  RGB_COL_BLACK
};

extern void start_status_led_thread(void);
extern void choose_col(status_led_col colour);

#endif 