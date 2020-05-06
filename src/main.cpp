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
  //chThdCreateStatic(waThread1, sizeof(waThread1),
  //  NORMALPRIO + 2, Thread1, NULL);
  Serial.begin(115200);
}
//------------------------------------------------------------------------------
void setup() {
  // Initialize OS and then call chSetup.
  pinMode(LED_BUILTIN, OUTPUT);
  chBegin(chSetup);
  // chBegin() resets stacks and should never return.
  while (true) {}
}

uint16_t buff_place = 0; 
void loop() {
  if(Serial.available() > 0){
    proto_testing_buffer[buff_place] = Serial.read();
    buff_place++; 

    // Reset when we get to 127
    if(buff_place < 127){
      buff_place = 0; 
      // Unpacking the message. 
      BoardStatus board_status; 
      pb_istream_t stream_in  = pb_istream_from_buffer(proto_testing_buffer, sizeof(proto_testing_buffer));
      pb_decode(&stream_in, BoardStatus_fields, &board_status);

      Serial.print("Board Free Memory: ");
      Serial.println(board_status.free_mem_kb);
    }
  }  
}

void protobuffer_testing(void){
}