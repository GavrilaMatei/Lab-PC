// Objectives:
// 1. configure UART on ATmega328p
// 2. write bytes on UART
// 3. receive bytes on UART
// 4. text protocols

// Components
// 2 LEDs + resistors
// 1 Push Button + resistor

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include <Uart.h>

Uart uart;
char buf[1024];
int bufidx=0;
bool led1ctrl=true;//is on?
bool led2ctrl=false;//is enabled?
int cnt=0;

void setup() {
    // initialize GDB stub
    uart.init();
    //button
    DDRD &= ~(1 << 2); 
    //leds
    DDRD |= (1 << 4);
    DDRD |= (1 << 7);
    PORTD &= ~(1 << 4); 
}
void responseBack(const char* userMsg) {
    uart.writeString("You said: ");
    uart.writeString(userMsg);
    uart.writeByte('\n');
}

void buttonCheck(){
    unsigned char btn = PIND & (1 << 2); 
    if(btn != 0)
        uart.writeString("Butonul e apasat");
    else
        uart.writeString("Butonul nu e apasat");
}

void led1OnOff(){
    if(led1ctrl==true){
        PORTD |= (1 << 4); //turn off
        led1ctrl = false;
    } 
    else if(led1ctrl!=true){
        PORTD &= ~(1 << 4); //turn on
        led1ctrl = true;
    }
}

void led2OnOff(){
//to do : oscilating led
    if(led2ctrl==true){
        if(cnt<=5){
            PORTD &= ~(1 << 7);
        }
        if(cnt>5){
            PORTD &= ~(1 << 7);
        }
        if(cnt==7)
            cnt=0;
    }
}

void loop() {
    // TODO: 3. buffer bytes from user and when reach newline(\n) send the buffer back - use responseBack(...)
    if(uart.available()){
        char c = uart.readByte();
        if(c == '\n'){
            buf[bufidx]='\0';
            if(strcasecmp(buf,"btn")==0){
                buttonCheck();
            }
            if(strcasecmp(buf,"led1")==0){
                led1OnOff();
            }
            if(strcasecmp(buf,"led2")==0){
                led2ctrl=!led2ctrl;
            }
            responseBack(buf);
            bufidx=0;
        }
        else if (c!='\r')
        {
            buf[bufidx++]=c;
        }
    }
    // TODO: 4. implement a text protocol with the following minimal features:
    //  - one button to read state (pressed or not) done i think
    //  - one led to set state (on or off)
    //  - one blinking led (500ms on, 200ms off) and enable or disable it
    // DO NOT BLOCK THE MCU
    // HINT: standalone timer, internal timer, multiple options
    led2OnOff();
}