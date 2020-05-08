// ChibiOS files.
#include "ChRt.h"
#include "MessageManagement.hpp"
#include "StripManagement.hpp"
#include "MatrixManagement.hpp"

MessageManagement message_management; 
StripManagement strip_management; 

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

    thread_end_tick = thread_begin_tick + TIME_I2MS(10);
    if(thread_end_tick > chVTGetSystemTimeX())
          chThdSleepUntil(thread_end_tick);   
  }
}

void chSetup() {
  message_management.begin();
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
  // Running our message management on the main loop thread. 
  message_management.run();
  // Wait about 5 milliseconds between processing requests
  chThdSleepMilliseconds(7);
}