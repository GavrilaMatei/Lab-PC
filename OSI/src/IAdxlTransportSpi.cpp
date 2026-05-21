#include <Arduino.h>
#include <IAdxlTransportSpi.h>
#include <SpiMaster.h>

SpiMaster spi;


void ADXL_enable() {
    //select ADXL
    PORTD &= ~(1<<7);
}

void ADXL_disable() {
    //deselect ADXL
    PORTD |=(1<<7);
}

char IAdxlTransportSpi :: cmdBuilder(char addr, bool rw, bool mb) {
    return (addr & 0b00111111) | (mb << 6) | (rw << 7); //sets r/w bit and multiple byte pin
}

void IAdxlTransportSpi ::init(){
    spi.init();
    DDRD|=(1<<7); //chip select @ pin 7
}

bool IAdxlTransportSpi ::read(int addr, char *d,int len){
    ADXL_enable();
    
    if(len > 1)
        spi.transmit(cmdBuilder(addr,1,1));
    else if(len == 1)
        spi.transmit(cmdBuilder(addr,1,0));
    for(int i = 0; i<len;i++){
        d[i] = spi.transmit(0x00);
    }
    ADXL_disable();
    return true;
}

bool IAdxlTransportSpi ::write(int addr,const char* d,int len){
    ADXL_enable();

    if(len > 1)
        spi.transmit(cmdBuilder(addr,0,1));
    else if(len == 1)
        spi.transmit(cmdBuilder(addr,0,0));
    for(int i = 0;i < len; i++){
        spi.transmit(d[i]);
    }
    
    ADXL_disable();
    return true;
}
