#include <Arduino.h>
#include <IAdxlTransportI2C.h>
#include <I2cMaster.h>
#include <Uart.h>

#define ADX345_I2C_ADDR 0x53

I2cMaster i2c;

void IAdxlTransportI2C :: init(){
    i2c.init();
}

bool IAdxlTransportI2C :: write(int addr, const char* d,int len){
    i2c.sendStart();
    i2c.writeAddrWrite(ADX345_I2C_ADDR);
    i2c.writeByte(addr);
    for(int i = 0;i<len;i++){
        i2c.writeByte(d[i]);
    }
    i2c.sendStop();
}

bool IAdxlTransportI2C :: read(int addr, char* d,int len){
    i2c.sendStart();
    i2c.writeAddrWrite(ADX345_I2C_ADDR);
    i2c.writeByte(addr);
    i2c.sendStart();
    i2c.writeAddrRead(ADX345_I2C_ADDR);
    for(int i = 0; i < len ; i++){
        if(i==len-1)
            i2c.readByte(d[i],false);
        else
            i2c.readByte(d[i],true);
    }
    i2c.sendStop();
}


