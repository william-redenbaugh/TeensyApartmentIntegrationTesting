#include "status_led_thread.hpp"

MUTEX_DECL(status_led_mutex);

// Status LED object
StatusLED status_led;

// Thread handler for status LED. 
thread_t *status_thread; 

// The color that we flash once
status_led_col flash_col; 

// Color that is currently blinking. 
volatile status_led_col current_blink_col = RGB_COL_BLUE;

extern void status_signal_once(status_led_col colour);
extern void status_change_flash(status_led_col colour);
void set_col(status_led_col colour);
extern void start_status_led_thread(void);

/**************************************************************************/
/*!
    @brief External function that let's us choose an enumerated color type. This non-blocking command tell's the status LED to signal a different color. 
*/
/**************************************************************************/
extern void status_signal_once(status_led_col colour){
  chMtxLock(&status_led_mutex);
  flash_col = colour;
  chMtxUnlock(&status_led_mutex);
  chEvtSignal(status_thread, EVENT_MASK(0));
}

/**************************************************************************/
/*!
    @brief Change the color the the Status LED is always flashing. 
*/
/**************************************************************************/
extern void status_change_flash(status_led_col colour){
  current_blink_col = colour;
}

/**************************************************************************/
/*!
    @brief Helper function that let's us set the different colors based off the available enumerations. 
*/
/**************************************************************************/
void set_col(status_led_col colour){
  // Which color are we setting next. 
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

    // We really should never get here...
    default:
    break;
  }
}

// Status LED thread working space and actual thread function. 
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
    if(m & EVENT_MASK(0)){
      chMtxLock(&status_led_mutex);
      set_col(flash_col); 
      chMtxUnlock(&status_led_mutex);
    }
    else
      status_led.black();
    
    // Choose fade events. 
    m = chEvtWaitAnyTimeout(ALL_EVENTS, 1000);
    if(m & EVENT_MASK(0)){
      chMtxLock(&status_led_mutex);
      set_col(flash_col);
      chMtxUnlock(&status_led_mutex);
    }
    else
      set_col(current_blink_col);
  }
}

/**************************************************************************/
/*!
    @brief Allows us to start up our status LED thread. 
*/
/**************************************************************************/
extern void start_status_led_thread(void){
    // Enable our status LED thread, last so we know all other threads have
    // been enabled. 
    chThdCreateStatic(status_led_thread_wa, 
                      sizeof(status_led_thread_wa), 
                      NORMALPRIO + 3, 
                      status_led_thread, 
                      NULL);
}