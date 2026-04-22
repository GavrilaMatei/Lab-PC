#include <Uart.h>
#include <string.h>
#include <Arduino.h>

int ubrr=103;
void Uart::init() {
    // TODO: 1. configure UART
    // set UART pin directions

    DDRD &= ~(1 << 0);//intrare
    DDRD |= (1 << 1 );//iesire

    // set baud rate 9600
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    // enable RX and TX
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    // set frame format: 8 bits, 1 stop bit, no parity
    UCSR0C = (3<<UCSZ00);

    // DO NOT CHANGE ALL BITS
}

void Uart::writeByte(const char& d) {
    // TODO: 2. implement write + test it and capture on oscilloscope
    // wait to empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    // write data
    UDR0 = d;
}

bool Uart::available() {
    // TODO: 3. check if are data in UART buffer'
    if((UCSR0A & (1<<RXC0)) != 0)
    {
        return true;
    }
    return false;
}

char Uart::readByte() {
    // TODO: 3. implement read
    // wait for data
    while(!available());
    // read data and return it
    return UDR0;
}

void Uart::writeString(const char* msg) {
    for (int i = 0; i < strlen(msg); i++)
        writeByte(msg[i]);
}
void Uart::writeIntegerNumber(const int &number, const int &base) {
    
}
