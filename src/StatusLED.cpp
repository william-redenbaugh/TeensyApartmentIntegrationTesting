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

void StatusLED::begin(void){
    SPI.begin();
    SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE3)); 
    this->set_led(0, 0, 0);
    this->update();
}

void StatusLED::set_led(uint8_t r, uint8_t g, uint8_t b){
    for(uint8_t pos = 0; pos < 4; pos++){
        this->dma_out_arr[pos] = get_protocol_eq(g, pos);
        this->dma_out_arr[pos + BYTES_FOR_LED_BYTE] = get_protocol_eq(r, pos);
        this->dma_out_arr[pos + BYTES_FOR_LED_BYTE * 2] = get_protocol_eq(b, pos);
    }
}

void StatusLED::update(void){
    SPI.transfer(this->dma_out_arr, this->dma_rec, sizeof(dma_out_arr), this->event_responder);
}

void StatusLED::set_start(void){
    this->set_led(100, 100, 100);
    this->update();
}

void StatusLED::rtos_enabled(void){
    this->set_led(0, 0, 100);
    this->update();
}

void StatusLED::red(void){
  this->set_led(100, 0, 0);
  this->update();
}

void StatusLED::green(void){
  this->set_led(0, 100, 0);
  this->update();
}

void StatusLED::blue(void){
  this->set_led(0, 0, 100);
  this->update();
}

void StatusLED::white(void){
  this->set_led(100, 100, 100);
  this->update();
}

void StatusLED::black(void){
  this->set_led(0, 0, 0);
  this->update();
}
