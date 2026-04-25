#include <Arduino.h>
#include <I2cMaster.h>
/*

sda - sda
sclk - sck
3v3 - cs

0x00 - 0xE5
0x1D - adxl addr

Port4-sda
Port5-clk

twbr = 12
twsr = f8
*/
void I2cMaster::_writeByte(const char& data) {
    // TODO: 2. send 1 byte on I2C
    // write byte
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    // send command to send byte
    // wait for ack or nack
    while (!(TWCR & (1<<TWINT)));
}

void I2cMaster::_readByte(char& data) {
    // TODO: 2. read 1 byte from I2C
    // send command to read byte
    TWCR = (1<<TWINT) |(1<<TWEN);
    // wait for ack or nack
    while (!(TWCR & (1<<TWINT)));
    // read byte
    data = TWDR;
}

void I2cMaster::init() {
    // TODO: 1. configure SPI for master mode
    // set frequency; read datasheet for SCLK frequency
    TWBR = 12;
    TWSR =  0;
    // set SCLK pin output
    DDRC |= (1<<5);
    // enable internal pull up resistor for SCLK and SDA, set PORTxn = 1
    PORTC |= (1<<5) | (1<<4);
}

void I2cMaster::sendStart() {
    // TODO: 2. send I2C start condition
    // send start condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    // wait for start has been transmitted
    while (!(TWCR & (1<<TWINT)));
}

bool I2cMaster::writeAddrWrite(const char& addr) {
    // TODO: 2. send slave addr for write
    // add write bit to addr {addr[6:0],r/w}
    _writeByte(addr<<1 );
    // check if ack received for addr

    return ((TWSR & (0xf8)) == 0x18);
}

bool I2cMaster::writeAddrRead(const char& addr) {
    // TODO: 2. send slave addr for read
    // add read bit to addr {addr[6:0],r/w}
    _writeByte(addr<<1 | 1<<0);
    // check if ack received for addr
    return false;
}

bool I2cMaster::writeByte(const char& d, I2cResponse expectedResponse) {
    // TODO: 2. send byte on I2C
    // send byte
    _writeByte(d);
    // retrun if ack received
    return false;
}

bool I2cMaster::readByte(char& d, I2cResponse expectedResponse) {
    // TODO: 2. read byte from I2C
    _readByte(d);
    // retrun if ack received
    return false;
}

void I2cMaster::sendStop() {
    // TODO: 2. send I2C stop condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}