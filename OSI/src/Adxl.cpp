#include <Adxl.h>

bool Adxl :: isConnected(){
    char devId;
    transport->read(0x00, &devId, 1);

    return devId == 0xE5;      
}

void Adxl ::start(){
    char val = 0x08;
    transport->write(0x2d, &val, 1);
}

void Adxl ::stop(){
    char val = 0x00;
    transport->write(0x2d, &val, 1);
}

void Adxl ::readData() {
    char buf[6];
    transport->read(0x32, buf, 6);
}