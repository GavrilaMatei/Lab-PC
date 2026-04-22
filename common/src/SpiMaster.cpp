#include <SpiMaster.h>
#include <Arduino.h>
/*
 teorie
 3.3 V adxl
 configuram spi
 fclk   <=5mHZ
 CPLO   1
 CPHA   1
 DIR    msb first 

 13 sclk-clk
 11 mosi-sda
 12 miso-sdo
 7 cs-cs

 5v  - hv-gnd
 3v3 - lv-gnd

 1-read

 reg map 
0x800x00
xx0XE5

4,8,16clk

*/
void SpiMaster::init() {
    // TODO: 1. configure SPI
    /* ---!VERY IMPORTANT!--- */
    // write 1 on CS after set CS as OUTPUT
    // in the end configure SPI
    // set MOSI, SCK - output
    /* Set MOSI 11 and SCK 13 output, all others input */
    DDRB = (1<<DDB3)|(1<<DDB5)|(1<<DDB2);
    PORTB|=(1<<2); //set SS 1
    // set MISO 12 - input
    DDRB &= ~(1<<DDB4);
    // enable SPI as master
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPOL)|(1<<CPHA);
    // check ADXL datasheet for clock frequency -2MHz
    // check ADXL datasheet for clock polarity
    // check ADXL datasheet for clock phase
}

char SpiMaster::transmit(const char& d) {
    // TODO: 2. transmit 1 byte on SPI
    // start transmission
    SPDR = d;
    // wait for transmission complete
    while(!(SPSR & (1<<SPIF)))
    ;
    // return response from slave
    return SPDR;
}