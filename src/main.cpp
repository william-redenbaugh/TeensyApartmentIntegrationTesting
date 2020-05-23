// ChibiOS files.
#include "ChRt.h"
#include "MessageManagement.hpp"
#include "StripManagement.hpp"

#include "MatrixManagement.hpp"
#include <SPI.h>
#include "OctoWS2811.h"

// Application Level programs
#include "status_led_thread.h"

// Message management handler, lets us deal with messaging stuff in another thread. 
MessageManagement message_management; 

// Strip management, where we will deal with strip animations and pushing data to the pixels. 
StripManagement strip_management; 

// Same thing as strip management except for it's for a led matrix instead. 
MatrixManagement matrix_management; 

systime_t message_thread_begin_tick; 
systime_t message_thread_end_tick;

// Static function for working on our strip thread. 
static THD_WORKING_AREA(strip_thread_working_area, 2048);
static THD_FUNCTION(strip_thread, arg){
    (void)arg;
    // Gotta call that begin command for our strip management!
    strip_management.begin();
    
    systime_t thread_begin_tick;
    systime_t thread_end_tick;
    while(1){
        thread_begin_tick = chVTGetSystemTimeX();
        // Just running strip stuff here!
        strip_management.run();

        // Just protecting our ass while trying to keep
        // Timings as reliable as possible. 
        // Basically we want to have consistent 10ms
        // Delays between stuff but if processing takes more than 
        // 10 ms we can put that shit here. 
        thread_end_tick = thread_begin_tick + TIME_I2MS(10);
        if(thread_end_tick > chVTGetSystemTimeX())
          chThdSleepUntil(thread_end_tick);  
    }
}

// Static function for working on our matrix thread. 
static THD_WORKING_AREA(matrix_thread_working_area, 6144);
static THD_FUNCTION(matrix_thread, arg){
  (void)arg; 
  systime_t thread_begin_tick;
  systime_t thread_end_tick; 
  while(1){
    thread_begin_tick = chVTGetSystemTimeX();

    matrix_management.begin();    

    thread_end_tick = thread_begin_tick + TIME_I2MS(10);
    if(thread_end_tick > chVTGetSystemTimeX())
          chThdSleepUntil(thread_end_tick);   
  }
}

void chSetup() {
  message_management.begin();
  strip_management.begin();
  matrix_management.begin();

  start_status_led_thread();
  
  // Creates a thread for pushing data to the led strips(via dma)
  chThdCreateStatic(strip_thread_working_area, 
                    sizeof(strip_thread_working_area), 
                    NORMALPRIO + 1, 
                    strip_thread, 
                    NULL);

  chThdCreateStatic(matrix_thread_working_area, 
                    sizeof(matrix_thread_working_area), 
                    NORMALPRIO + 2, 
                    matrix_thread, 
                    NULL);
}

void setup() {
  // We do all of our setup in here. 
  chBegin(chSetup);
  // chBegin() resets stacks and should never return.
  while (true) {}
}

void loop() {
  message_thread_begin_tick = chVTGetSystemTimeX();
  // Running our message management on the main loop thread. 
  message_management.run();
  // Wait about 5 milliseconds between processing requests

  // So we have the whole system run every 7 milliseconds. 
  message_thread_end_tick = message_thread_begin_tick + TIME_I2MS(7);
  if(message_thread_end_tick > chVTGetSystemTimeX())
    chThdSleepUntil(message_thread_end_tick);
}