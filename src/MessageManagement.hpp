#ifndef _MESSAGEMANAGEMENT_HPP
#define _MESSAGEMANAGEMENT_HPP
#include "Arduino.h"

// Protobuffer Stuff. 
#include "pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

// Our message data. 
#include "status.pb.h"
#include "messagedata.pb.h"
#include "general_instructions.pb.h"

class MessageManagement{
public: 
    // Initialization Sequence for Message management object
    void begin(void);
    
    // function to run for message management, should be running in void loop command
    // since that function has the most free stack space. 
    bool run(void);
    
    // Holds the latest message data. 
    MessageData_MessageType latest_message_enum(void);
    
    // Test code for making sure that the protobuffers are
    // packing and unpacking properly
    bool testing_message_protobuffers(void);

private:
    // Handler for processing general instructions. 
    void process_general_instructions(void);

    // Handler for processing matrix information
    void processing_matrix_information(void);

    // Handler for processing LED strip information
    void processing_led_strip_information(void);
    
    // Keeping track of the build in led state. 
    bool builtin_led_state = false; 

    // latest message data
    MessageData latest_message_data; 

};

#endif 
