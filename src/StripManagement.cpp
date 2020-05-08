#include "StripManagement.hpp"

static THD_WORKING_AREA(strip_thread_working_area, 2048);
static THD_FUNCTION(strip_thread, arg){
    //StripManagement *strip_management_ptr = arg; 
    (void)arg;
    while(1){
        // Try to do as much as possible in here :0
        //strip_management_ptr->run();
        Serial.println("Hello world!");
        chThdSleepSeconds(1);
    }
}

void StripManagement::begin(void){

}

void StripManagement::run(void){
    
}