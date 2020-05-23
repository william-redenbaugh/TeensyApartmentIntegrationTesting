#include "status_led_thread.h"

// Status LED
StatusLED status_led; 
thread_t *status_thread; 
status_led_col col; 

void choose_col(status_led_col colour){
  switch(colour){
  case(RGB_COL_RED):
  status_led.red();
  break;
  case(RGB_COL_GREEN):
  status_led.green();
  break;
  case(RGB_COL_BLUE):
  status_led.blue();
  break;
  case(RGB_COL_WHITE):
  status_led.white();
  break;
  case(RGB_COL_BLACK):
  status_led.black();
  break;
  }
}

static THD_WORKING_AREA(status_led_thread_wa, 512);
static THD_FUNCTION(status_led_thread, arg){
  (void)arg;
  status_thread = chThdGetSelfX();
  // Setup our status LED.
  status_led.begin();

  // Event mask allowing us to get events from other
  // Threads. 
  eventmask_t m;
  while(1){
    // Choose fade events. 
    m = chEvtWaitAnyTimeout(ALL_EVENTS, 1000);
    if(m & EVENT_MASK(0))
      choose_col(col); 
    else
      status_led.black();
    
    // Choose fade events. 
    m = chEvtWaitAnyTimeout(ALL_EVENTS, 1000);
    if(m & EVENT_MASK(0))
      choose_col(col);
    else
      status_led.blue();
  }
}

void start_status_led_thread(void){
    // Enable our status LED thread, last so we know all other threads have
    // been enabled. 
    chThdCreateStatic(status_led_thread_wa, 
                      sizeof(status_led_thread_wa), 
                      NORMALPRIO + 3, 
                      status_led_thread, 
                      NULL);
}