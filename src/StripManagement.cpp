#include "StripManagement.hpp"

void DMASPIStrip::begin(void){
    SPI.begin();
    SPI.beginTransaction(SPISettings(1600000, MSBFIRST, SPI_MODE0));
    
}

void StripManagement::begin(void){
    
}

void StripManagement::run(void){
    
}