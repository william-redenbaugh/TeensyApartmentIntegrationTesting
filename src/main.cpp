// Arduino files 
#include "Arduino.h"

// ChibiOS files.
#include "ChRt.h"

// Application Level programs
#include "status_led_thread.hpp"
#include "matrix_thread.hpp"
#include "strip_thread.hpp"
#include "message_management_thread.hpp"
#include "MessageManagement.hpp"

void chSetup() {
  start_message_management();
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