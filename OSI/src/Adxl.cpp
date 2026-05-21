#include <Adxl.h>

char buf[6];

void Adxl :: init(){
    transport->init();
}

bool Adxl :: isConnected(){
    char devId;
    transport->read(0x00, &devId, 1);

    return devId == (char)0xE5;      //returns true if correct dvID is read
}

void Adxl ::startMeasure(){
    char val = 0x08;
    transport->write(0x2d, &val, 1);
}

void Adxl ::stopMeasure(){
    char val = 0x00;
    transport->write(0x2d, &val, 1);
}

void Adxl ::readData() {
    transport->read(0x32, buf, 6); //buf has values of coords {x0,x1,y0,y1,z0,z1}
}

int Adxl :: getX(){
    int x = ((int)buf[1]<<8)|buf[0];
    return x;
}

int Adxl :: getY(){
    int x = ((int)buf[3]<<8)|buf[2];
    return x;
}

int Adxl :: getZ(){
    int x = ((int)buf[5]<<8)|buf[4];
    return x;
}