// Arduino files 
#include "Arduino.h"

// ChibiOS files.
#include "ChRt.h"

// Application Level programs
#include "status_led_thread.hpp"
#include "matrix_thread.hpp"
#include "strip_thread.hpp"
#include "MessageManagement.hpp"

// Message management handler, lets us deal with messaging stuff in another thread. 
MessageManagement message_management; 

systime_t message_thread_begin_tick; 
systime_t message_thread_end_tick;

void chSetup() {
  message_management.begin();

  start_status_led_thread();
  start_matrix_thread();
  start_strip_thread();
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