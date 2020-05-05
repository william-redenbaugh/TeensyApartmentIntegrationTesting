// Example to demonstrate thread definition, semaphores, and thread sleep.
#include "ChRt.h"
#include "pb.h"
#include "status.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "pb.h"

void protobuffer_testing(void);

// LED_BUILTIN pin on Arduino is usually pin 13.

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);
//------------------------------------------------------------------------------
// Thread 1, turn the LED off when signalled by thread 2.
//
// 64 byte stack beyond task switch and interrupt needs.
static THD_WORKING_AREA(waThread1, 64);

static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  while (!chThdShouldTerminateX()) {
    // Wait for signal from thread 2.
    chSemWait(&sem);

    // Turn LED off.
    digitalWrite(LED_BUILTIN, LOW);
    protobuffer_testing();
  }
}
//------------------------------------------------------------------------------
// Thread 2, turn the LED on and signal thread 1 to turn the LED off.
//
// 64 byte stack beyond task switch and interrupt needs.
static THD_WORKING_AREA(waThread2, 64);

static THD_FUNCTION(Thread2, arg) {
  (void)arg;
  pinMode(LED_BUILTIN, OUTPUT);
  while (true) {
    digitalWrite(LED_BUILTIN, HIGH);

    // Sleep for 200 milliseconds.
    chThdSleepMilliseconds(1000);

    // Signal thread 1 to turn LED off.
    chSemSignal(&sem);

    // Sleep for 200 milliseconds.
    chThdSleepMilliseconds(1000);
  }
}
//------------------------------------------------------------------------------
// continue setup() after chBegin().
void chSetup() {
  // Start threads.
  chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
    NORMALPRIO + 1, Thread2, NULL);
}
//------------------------------------------------------------------------------
void setup() {
  // Initialize OS and then call chSetup.
  chBegin(chSetup);
  // chBegin() resets stacks and should never return.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() is the main thread.  Not used in this example.
void loop() {

}

void protobuffer_testing(void){
  BoardStatus board_status; 
  board_status.free_mem_kb = 490; 
  board_status.status = 1; 

  uint8_t buffer[128];
  size_t msg_len = sizeof(buffer); 

  pb_ostream_t stream_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
  pb_encode(&stream_out, BoardStatus_fields, &board_status);

  pb_istream_t stream_in  = pb_istream_from_buffer(buffer, sizeof(buffer));
  
  BoardStatus board_status_in; 
  pb_decode(&stream_in, BoardStatus_fields, &board_status_in);

  Serial.print("Board Free Memory: ");
  Serial.println(board_status_in.free_mem_kb);

}