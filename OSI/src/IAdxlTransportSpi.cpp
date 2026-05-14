#include <Arduino.h>
#include <IAdxlTransportSpi.h>
#include <SpiMaster.h>
#include <Uart.h>

SpiMaster spi;


void ADXL_enable() {
    // TODO: 2. select ADXL
    PORTD &= ~(1<<7);
}

void ADXL_disable() {
    // TODO: 2. deselect ADXL
    PORTD |=(1<<7);
}

void IAdxlTransportSpi ::init(){
    spi.init();
    DDRD|=(1<<7);
}
bool IAdxlTransportSpi ::read(int addr, char *d,int len){
    ADXL_enable();
    
    if(len > 1)
        spi.transmit((addr & 0b00111111) | 1<<6 | 1<<7);
    else if(len == 1)
        spi.transmit((addr & 0b00111111) | 1<<7);
    for(int i = 0; i<len;i++){
        d[i] = spi.transmit(0x00);
    }

    ADXL_disable();
}

bool IAdxlTransportSpi ::write(int addr,const char* d,int len){
    ADXL_enable();

    if(len > 1)
        spi.transmit((addr & 0b00111111) | 1<<6);
    else if(len == 1)
        spi.transmit((addr & 0b00111111));
    for(int i = 0;i < len; i++){
        spi.transmit(d[i]);
    }
    
    ADXL_disable();
}