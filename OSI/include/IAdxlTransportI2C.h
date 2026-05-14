#include <IAdxlTransport.h>
#ifndef I_ADXL_TRANSPORT_I2C_H
#define I_ADXL_TRANSPORT_I2C_H

class IAdxlTransportI2C : public IAdxlTransport{
    void init();
    bool write(int addr, const char* d,int length);
    bool read(int addr, char* d,int length);
};


#endif