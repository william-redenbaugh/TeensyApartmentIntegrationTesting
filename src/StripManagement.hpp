#ifndef _STRIPMANAGEMENT_HPP
#define _STRIPMANAGEMENT_HPP

#include <Arduino.h>
#include "ChRt.h"
#include <SPI.h>

#define NB_COLORS 3
#define BYTES_FOR_LED_BYTE 4
#define BYTES_FOR_LED BYTES_FOR_LED_BYTE*NB_COLORS

class DMASPIStrip{
    public: 
        bool begin(uint8_t *in_arr, uint8_t *out_arr, SPIClass *spi, uint16_t num_leds);
        void set_led(uint16_t led, uint8_t r, uint8_t g, uint8_t b); 
        void update(void);

    private: 
        SPIClass *spi; 
        uint16_t num_leds = 0; 
        uint8_t *dma_out_arr;
        uint8_t *dma_rec;
        EventResponder event_responder; 
};

class StripManagement{
    public: 
        void begin(void);
        
        void run(void);
    private: 
};

#endif