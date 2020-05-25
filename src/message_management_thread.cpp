#include "message_management_thread.hpp"
#include "status_led_thread.hpp"

// Message management handler, lets us deal with messaging stuff in another thread. 
MessageManagement message_management; 

systime_t message_thread_begin_tick; 
systime_t message_thread_end_tick;

extern void start_message_management(void);
extern void loop(void);

/**************************************************************************/
/*!
    @brief Allows us to start up the message management stuff. 
*/
/**************************************************************************/
extern void start_message_management(void){
    message_management.begin();
}

/**************************************************************************/
/*!
    @brief Where our message management stuff sits.(in our main thread. )
*/
/**************************************************************************/
extern void loop(void) {
/*
  message_thread_begin_tick = chVTGetSystemTimeX();
  // Running our message management on the main loop thread. 
  message_management.run();
  // Wait about 5 milliseconds between processing requests

  // So we have the whole system run every 7 milliseconds. 
  message_thread_end_tick = message_thread_begin_tick + TIME_I2MS(7);
  if(message_thread_end_tick > chVTGetSystemTimeX())
    chThdSleepUntil(message_thread_end_tick);

*/

    chThdSleepSeconds(2);
    status_change_flash(RGB_COL_GREEN);
    chThdSleepSeconds(2);
    status_change_flash(RGB_COL_BLUE);
    chThdSleepSeconds(2);
    status_change_flash(RGB_COL_WHITE);
    chThdSleepSeconds(2);
    status_change_flash(RGB_COL_RED);
}

