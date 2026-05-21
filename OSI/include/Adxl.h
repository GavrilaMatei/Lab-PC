#include <IAdxlTransport.h>
#ifndef ADXL_H
#define ADXL_H

class Adxl{
private:
    IAdxlTransport* transport;
public :
        Adxl(IAdxlTransport* _transport){
            transport = _transport;
        }
        void init();

        bool isConnected();     //checks deviceID
        void startMeasure();
        void stopMeasure();

        void readData();        //adds values to the buffer
        int getX();             //returns coords
        int getY();             //returns coords
        int getZ();             //returns coords
};


// TODO: 2. implement Adxl high level class
// * will get an IAdxlTransport* in constructor
// need to provide the fallowing functions:
//  - check if sensor is connected by read and check device id
//  - start/stop measurement
//  - read data from sensor, not return them
//  - get the values for every axis from independent functions
//  - two consecutive read from same axis will automaticaly will update values the second time

#endif