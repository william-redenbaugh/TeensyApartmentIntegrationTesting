// ChibiOS files.
#include "ChRt.h"
#include "MessageManagement.hpp"

MessageManagement message_management; 

void chSetup() {
  message_management.begin();
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