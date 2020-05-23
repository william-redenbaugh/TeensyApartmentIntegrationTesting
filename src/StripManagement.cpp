#include "StripManagement.hpp"

static uint8_t get_protocol_eq(uint8_t data, int pos){
  uint8_t eq = 0;
  if (data & (1 << (2*(3-pos))))
    eq = 0b1110;
  else
    eq = 0b1000;
  if (data & (2 << (2*(3-pos))))
    eq += 0b11100000;
  else
    eq += 0b10000000;
  return eq;
}

bool DMASPIStrip::begin(uint8_t *in_arr, uint8_t *out_arr, SPIClass *spi, uint16_t num_leds){
    this->spi = spi; 

    SPI.begin();
    SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE3));
    this->num_leds = num_leds; 

    this->dma_out_arr = (uint8_t*)malloc((num_leds * BYTES_FOR_LED + 64) * sizeof(uint8_t));
    this->dma_rec = (uint8_t*)malloc((num_leds * BYTES_FOR_LED + 32) * sizeof(uint8_t));
    return true; 
}

void DMASPIStrip::set_led(uint16_t led, uint8_t r, uint8_t g, uint8_t b){
    for(uint8_t pos = 0; pos < 4; pos++){
        this->dma_out_arr[BYTES_FOR_LED*led + pos] = get_protocol_eq(g, pos);
        this->dma_out_arr[BYTES_FOR_LED*led + pos + BYTES_FOR_LED_BYTE] = get_protocol_eq(r, pos);
        this->dma_out_arr[BYTES_FOR_LED*led + pos + BYTES_FOR_LED_BYTE * 2] = get_protocol_eq(b, pos);
    }
}

void DMASPIStrip::update(void){
    SPI.transfer(this->dma_out_arr, this->dma_rec, sizeof(dma_out_arr), this->event_responder);
}

void StripManagement::begin(void){
    
}

void StripManagement::run(void){
    
}