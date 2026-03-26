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
    DDRB |= (1 << 1);
    PORTB |= (1<<1);
    PORTD &= ~(1 << 4); //led1on
}
void responseBack(const char* userMsg) {
    uart.writeString("You said: ");
    uart.writeString(userMsg);
    uart.writeByte('\n');
}

void buttonCheck(){
    unsigned char btn = PIND & (1 << 2); 
    if(btn != 0)
        uart.writeString("Butonul e apasat \n");
    else
        uart.writeString("Butonul nu e apasat \n");
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
        TCCR1A =(0b10<<0)|(0b11<<6);
        TCCR1B =(0b11<<3)|(0b101<<0);   
        ICR1 = 10937; //limita
        OCR1A = 7812;  //prag
    }
    else{
        TCCR1A = 0;
        TCCR1B = 0;
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