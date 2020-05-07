// Example to demonstrate thread definition, semaphores, and thread sleep.
#include "ChRt.h"
#include "pb.h"
#include "status.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "pb.h"
#include "messagedata.pb.h"

void testing_message_size_pb(void);

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);

static THD_WORKING_AREA(waThread1, 1024);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  while (!chThdShouldTerminateX()) {
    // Wait for signal from thread 2.
    chSemWait(&sem);

    // Turn LED off.
    digitalWrite(LED_BUILTIN, LOW);
    //protobuffer_testing();
  }
}

void chSetup() {
  // Start threads.
  //chThdCreateStatic(waThread1, sizeof(waThread1),
  //  NORMALPRIO + 2, Thread1, NULL);
  
  Serial.begin(115200);

  // Initialize OS and then call chSetup.
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup() {
  // We do all of our setup in here. 
  chBegin(chSetup);
  // chBegin() resets stacks and should never return.
  while (true) {}
}

void loop() {
  // Once we have 128 bytes in the array.
  if(Serial.available() >= 32){
    // Struct that we will store Message data in.
    MessageData message_data; 
    
    // Scoping it out so we don't take up too much stack space. 
    {
      uint8_t message_instr_arr[32];
      for(uint8_t i = 0; i < 32; i++)
        // Popping off all the oldest 32 bytes. 
        message_instr_arr[i] = Serial.read();

      // Message unpacking instructions. 
      pb_istream_t msg_in = pb_istream_from_buffer(message_instr_arr, 32);
      pb_decode(&msg_in, MessageData_fields, &message_data);
    }

    // Byte array with instruction information.
    uint8_t message_instr_arr[message_data.message_size];
    switch(message_data.message_type){
      // When we receive general instruction data. we do stuff here. 
      case(MessageData_MessageType_GENERAL_INSTRUCTIONS):
      break;


      // When we receive matrix data we. we do other stuff here!
      case(MessageData_MessageType_MATRIX_DATA):
      break;

      // if we get here. then we fucked up lol. 
      default:
      // Reads through whatever is left and clears the buffer. 
      while(Serial.available())
        Serial.read();
      break;
    }
  }  

  chThdSleepSeconds(1);
  testing_message_size_pb();
}

void testing_message_size_pb(void){
    MessageData message_data_out;
    message_data_out.message_size = 85785967;
    message_data_out.message_type = MessageData_MessageType_MATRIX_DATA;

    // Put data into serialized format. 
    uint8_t buffer[32];
    pb_ostream_t msg_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&msg_out, MessageData_fields, &message_data_out);

    // Unpack serialsed data. 
    pb_istream_t msg_in = pb_istream_from_buffer(buffer, 32);

    MessageData message_data_in; 
    pb_decode(&msg_in, MessageData_fields, &message_data_in);

    if(message_data_in.message_size == message_data_out.message_size && message_data_in.message_type == message_data_out.message_type){
      Serial.println("Protobuffer messages succeeded! :0 ");   
    }
}