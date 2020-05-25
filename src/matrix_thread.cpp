#include "matrix_thread.hpp"

// Same thing as strip management except for it's for a led matrix instead. 
MatrixManagement matrix_management; 

extern void start_matrix_thread(void);

// Static function for working on our matrix thread. 
static THD_WORKING_AREA(matrix_thread_working_area, 6144);
static THD_FUNCTION(matrix_thread, arg){
  (void)arg; 
  systime_t thread_begin_tick;
  systime_t thread_end_tick; 
  matrix_management.begin();

  while(1){
    thread_begin_tick = chVTGetSystemTimeX();
    
    thread_end_tick = thread_begin_tick + TIME_I2MS(10);
    if(thread_end_tick > chVTGetSystemTimeX())
          chThdSleepUntil(thread_end_tick);   
  }
}

/**************************************************************************/
/*!
    @brief Allows us to start up our matrix animation thread. 
*/
/**************************************************************************/
extern void start_matrix_thread(void){
    chThdCreateStatic(matrix_thread_working_area, 
                      sizeof(matrix_thread_working_area), 
                      NORMALPRIO + 2, 
                      matrix_thread, 
                     NULL);
}