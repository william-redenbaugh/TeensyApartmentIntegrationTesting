// Example to demonstrate thread definition, semaphores, and thread sleep.
#include "ChRt.h"
#include "pb.h"
#include "status.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "pb.h"

void protobuffer_testing(void);

uint8_t proto_testing_buffer[128];
// LED_BUILTIN pin on Arduino is usually pin 13.

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);
//------------------------------------------------------------------------------
// Thread 1, turn the LED off when signalled by thread 2.
//
// 64 byte stack beyond task switch and interrupt needs.
static THD_WORKING_AREA(waThread1, 1024);

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
// continue setup() after chBegin().
void chSetup() {
  // Start threads.
  chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);
}
//------------------------------------------------------------------------------
void setup() {
  // Initialize OS and then call chSetup.
  pinMode(LED_BUILTIN, OUTPUT);
  chBegin(chSetup);
  // chBegin() resets stacks and should never return.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() is the main thread.  Not used in this example.
void loop() {
  
  chThdSleepSeconds(1);
  // Packing up the message. 
  BoardStatus board_status; 
  board_status.free_mem_kb = 485; 
  board_status.status = 1; 
  pb_ostream_t stream_out = pb_ostream_from_buffer(proto_testing_buffer, sizeof(proto_testing_buffer));
  pb_encode(&stream_out, BoardStatus_fields, &board_status);
  
  // Signal thread 1 to turn LED off.
  chSemSignal(&sem);

  chThdSleepSeconds(1);
}

void protobuffer_testing(void){

  // Unpacking the message. 
  BoardStatus board_status; 
  pb_istream_t stream_in  = pb_istream_from_buffer(proto_testing_buffer, sizeof(proto_testing_buffer));
  pb_decode(&stream_in, BoardStatus_fields, &board_status);

  Serial.print("Board Free Memory: ");
  Serial.println(board_status.free_mem_kb);
}