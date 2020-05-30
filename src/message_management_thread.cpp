#include "message_management_thread.hpp"
#include "status_led_thread.hpp"
#include "status_led_thread.hpp"

// Message management handler, lets us deal with messaging stuff in another thread. 
MessageManagement message_management; 

systime_t message_thread_begin_tick; 
systime_t message_thread_end_tick;

extern void start_message_management(void);
extern void loop(void);

void run_general_instructions(void);

/**************************************************************************/
/*!
    @brief Allows us to start up the message management stuff. 
*/
/**************************************************************************/
extern void start_message_management(void){
    message_management.begin();
}

/**************************************************************************/
/*!
    @brief Where our message management stuff sits.(in our main thread. )
*/
/**************************************************************************/
extern void loop(void) {

  message_thread_begin_tick = chVTGetSystemTimeX();
  // Running our message management on the main loop thread. 
  if(message_management.run()){
        switch (message_management.latest_message_enum()){
        case (MessageData_MessageType_GENERAL_INSTRUCTIONS):
        run_general_instructions();
        break;
        case (MessageData_MessageType_MATRIX_DATA):
        break;

        case (MessageData_MessageType_LED_STRIP_DATA):
        break;
      
        default:
        break;
      }
  }
  
  // So we have the whole system run every 7 milliseconds. 
  message_thread_end_tick = message_thread_begin_tick + TIME_I2MS(7);
  if(message_thread_end_tick > chVTGetSystemTimeX())
    chThdSleepUntil(message_thread_end_tick);
}

/**************************************************************************/
/*!
    @brief Whenever we get new general instruction data, it should sit here. 
*/
/**************************************************************************/
void run_general_instructions(void){
    
    switch(message_management.get_latest_general_instructions()){
    case(GeneralInstructions_MainInstrEnum_DO_NOTHING):
    break;

    case(GeneralInstructions_MainInstrEnum_REBOOT):
    break;

    case(GeneralInstructions_MainInstrEnum_FREE_MEM):
    break;

    case(GeneralInstructions_MainInstrEnum_FLASH_LED):
    break;

    case(GeneralInstructions_MainInstrEnum_FLASH_GREEN):
    status_change_flash(RGB_COL_GREEN);
    break;

    case(GeneralInstructions_MainInstrEnum_FLASH_BLUE):
    status_change_flash(RGB_COL_BLUE);
    break;

    default:
    break;
    }
}

