// Objectives:
// 1. implement an OSI model for ADXL345 with I2C and SPI

#include "arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include "Adxl.h"
#include "IAdxlTransport.h"
#include "IAdxlTransportSpi.h"
#include "IAdxlTransportI2C.h"
#include "Uart.h"

// TODO: 1. based on IAdxlTransport interface implement two other classes
// - one I2cTransport for I2C protocol
// - one SpiTransport for SPI protocol

// TODO: 2. implement Adxl high level class
// * will get an IAdxlTransport* in constructor
// need to provide the fallowing functions:
//  - check if sensor is connected by read and check device id
//  - start/stop measurement
//  - read data from sensor, not return them
//  - get the values for every axis from independent functions
//  - two consecutive read from same axis will automaticaly will update values the second time

// TODO: 3. TEST IT!

// instantiation example: 
// Adxl adxl(new SpiTransport);

Uart uart;

Adxl adxl(new IAdxlTransportI2C); //I2C
// Adxl adxl(new IAdxlTransportSpi); //SPI

void setup() {
    uart.init();
    adxl.init();
    
    if(adxl.isConnected())
        uart.writeString("Sensor coonected \n");
    else 
        uart.writeString("error @ connection \n");
        
    adxl.startMeasure();
}

void loop() {
    adxl.readData();

    int x = adxl.getX();
    int y = adxl.getY();
    int z = adxl.getZ();
    
    uart.writeIntegerNumber(x,10);
    uart.writeByte(',');
    uart.writeIntegerNumber(y,10);
    uart.writeByte(',');
    uart.writeIntegerNumber(z,10);
    uart.writeByte('\n');

    delay(300);
}
