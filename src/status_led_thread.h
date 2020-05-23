#ifndef _STATUS_LED_THREAD_H
#define _STATUS_LED_THREAD_H

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

void start_status_led_thread(void);

#endif 