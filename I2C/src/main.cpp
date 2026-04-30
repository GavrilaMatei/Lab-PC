// Objectives:
// 1. configure I2C
// 2. comupaction over I2C
// 3. ADXL345 usage

// Components
// ADXL345 module
// Bidirectional level shifter

// Docs 
// ADXL345 Datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include <I2cMaster.h>
#include "Uart.h"

#define ADX345_I2C_ADDR 0x53

I2cMaster wire;
Uart uart;
char data;

char x0;    //0x32
char x1;    //0x33
char y0;    //0x34
char y1;    //0x35
char z0;    //0x36
char z1;    //0x37

void setup() {
    wire.init();
    uart.init();
    
    delay(500);
    // TODO: 2. read ADXL DEVICE ID
    wire.sendStart();
    wire.writeAddrWrite(ADX345_I2C_ADDR);
    wire.writeByte(0x00);
    wire.sendStart();
    wire.writeAddrRead(ADX345_I2C_ADDR);
    wire.readByte(data);
    wire.sendStop();
    uart.writeIntegerNumber(data,16);
    // expected response 0xE5

    delay(500);
    
    // TODO: 3. enable ADXL read
    wire.sendStart();
    wire.writeAddrWrite(ADX345_I2C_ADDR);
    wire.writeByte(0x2D);                   //power control register
    wire.writeByte(0x08);                   //mesure bit set 1 
    wire.sendStop();
    
    uart.writeByte('\n');
    delay(500);
}

void ADXL_readData() {
    // TODO: 3  . read X, Y, Z from ADXL and send to PC
    wire.sendStart();
    wire.writeAddrWrite(ADX345_I2C_ADDR);
    wire.writeByte(0x32);
    wire.sendStart();
    wire.writeAddrRead(ADX345_I2C_ADDR);
    wire.readByte(x0);
    wire.readByte(x1);
    wire.readByte(y0);
    wire.readByte(y1);
    wire.readByte(z0);
    wire.readByte(z1);
    wire.sendStop();
    
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
    delay(1000);
}
