#include <IAdxlTransport.h>
#ifndef I_ADXL_TRANSPORT_SPI_H
#define I_ADXL_TRANSPORT_SPI_H

class IAdxlTransportSpi : public IAdxlTransport{
    void init();
    bool read(int addr, char* d,int length);
    bool write(int addr, const char* d,int length);
    char cmdBuilder(char addr, bool rw, bool mb);


};

#endif