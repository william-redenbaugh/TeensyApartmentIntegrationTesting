#include "strip_thread.hpp"

extern void start_strip_thread(void);

// Strip management, where we will deal with strip animations and pushing data to the pixels. 
StripManagement strip_management; 

// Static function for working on our strip thread. 
static THD_WORKING_AREA(strip_thread_working_area, 2048);
static THD_FUNCTION(strip_thread, arg){
    (void)arg;
    // Gotta call that begin command for our strip management!
    strip_management.begin();
    
    systime_t thread_begin_tick;
    systime_t thread_end_tick;
    while(1){
        thread_begin_tick = chVTGetSystemTimeX();
        // Just running strip stuff here!
        strip_management.run();

        // Just protecting our ass while trying to keep
        // Timings as reliable as possible. 
        // Basically we want to have consistent 10ms
        // Delays between stuff but if processing takes more than 
        // 10 ms we can put that shit here. 
        thread_end_tick = thread_begin_tick + TIME_I2MS(10);
        if(thread_end_tick > chVTGetSystemTimeX())
          chThdSleepUntil(thread_end_tick);  
    }
}

/**************************************************************************/
/*!
    @brief Allows us to start up our strip thread. 
*/
/**************************************************************************/
extern void start_strip_thread(void){
    // Creates a thread for pushing data to the led strips(via dma)
    chThdCreateStatic(strip_thread_working_area, 
                      sizeof(strip_thread_working_area), 
                      NORMALPRIO + 1, 
                      strip_thread, 
                      NULL);
}