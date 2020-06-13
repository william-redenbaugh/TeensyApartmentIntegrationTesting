#ifndef _STRIPMANAGEMENT_HPP
#define _STRIPMANAGEMENT_HPP

#include <Arduino.h>
#include "ChRt.h"
#include <SPI.h>

#define NB_COLORS 3
#define BYTES_FOR_LED_BYTE 4
#define BYTES_FOR_LED BYTES_FOR_LED_BYTE*NB_COLORS

/**************************************************************************/
/*!
    @brief Class that allows us to have a status LED. 
*/
/**************************************************************************/
class StatusLED{
    public: 
        // Command to begin strip remotely. 
        void begin(void);
        void _begin_led(void);

        void set_led(uint8_t r, uint8_t g, uint8_t b); 
        void update(void);
        void set_start(void);
        void rtos_enabled(void);

        void red(void);
        void green(void);
        void blue(void);
        void white(void);
        void black(void);
        
    private: 
        uint8_t dma_out_arr[20];
        uint8_t dma_rec[20];
        EventResponder event_responder; 
        thread_t *status_thread; 
};

/**************************************************************************/
/*!
    @brief Class that will aid us in managing the strips attached to our teensy. 
*/
/**************************************************************************/

class StripManagement{
    public: 
        void begin(void);
        
        void run(void);
    private: 
};

#endif