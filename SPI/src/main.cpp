// Objectives:
// 1. configure SPI
// 2. comupaction over SPI
// 3. ADXL345 usage

// Components
// ADXL345 module
// Bidirectional level shifter

// Docs
// ADXL345 Datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf


// HINTS
// use UART lib from lab2 to send messages to PC
// use itoa to convert int to string

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include <SpiMaster.h>  
#include <Uart.h>

Uart uart;
SpiMaster spi;

void ADXL_enable() {
    // TODO: 2. select ADXL
    PORTD &= ~(1<<7);
}

void ADXL_disable() {
    // TODO: 2. deselect ADXL
    PORTD |=(1<<7);
}

char ADXL_cmdBuilder(char addr, bool rw, bool mb) {
    return (addr & 0b00111111) | (mb << 6) | (rw << 7);
}

void setup() {
    // initialize GDB stub

    // TODO: 1. set an CS pin and make it as output
    DDRD|=(1<<7);

    ADXL_disable();

    spi.init();
    uart.init();

    // TODO: 2. read ADXL DEVICE ID
    // analyze SPI protocol on oscilloscope
    // expected response 0xE5

    ADXL_enable();
    spi.transmit(0x80);
    char devid = spi.transmit(0x00); //device id 
    ADXL_disable();

    uart.writeIntegerNumber(devid, 16); //response
    uart.writeByte('\n');

    delay(500);
    
    // TODO: 3. enable ADXL read mode
    
    ADXL_enable();
    
    spi.transmit(0x2D);
    spi.transmit(0x08);

    ADXL_disable();

    delay(500);
}

void ADXL_readData() {
    // TODO: 3. read X, Y, Z from ADXL and send to PC
    ADXL_enable();
    spi.transmit(ADXL_cmdBuilder(0x32,1,1)); // cmd
    char x0 = spi.transmit(0x00); // data
    char x1 = spi.transmit(0x00); // data
    char y0 = spi.transmit(0x00); // data
    char y1 = spi.transmit(0x00); // data
    char z0 = spi.transmit(0x00); // data
    char z1 = spi.transmit(0x00); // data
    ADXL_disable();
    int x = ((int)x1<<8)|x0;
    uart.writeIntegerNumber(x,10);
    uart.writeByte(',');
    int y = ((int)y1<<8)|y0;
    uart.writeIntegerNumber(y,10);
    uart.writeByte(',');
    int z = ((int)z1<<8)|z0;
    uart.writeIntegerNumber(z,10);
    uart.writeByte('\n');
}

void loop() {
    ADXL_readData();
    delay(500);
}