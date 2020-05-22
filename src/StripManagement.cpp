#include "StripManagement.hpp"

void DMASPIStrip::begin(void){
    SPI1.begin();
    
    chThdSleepSeconds(5);

    if(SPI1.initDMAChannels()){
        digitalWrite(LED_BUILTIN, HIGH);
    }
    SPI1.end();
    //SPI.beginTransaction(SPISettings(1600000, MSBFIRST, SPI_MODE0));
    
}

void StripManagement::begin(void){
    
}

void StripManagement::run(void){
    
}