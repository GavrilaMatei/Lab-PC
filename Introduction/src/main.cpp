// Objectives:
// 1. presenting ATmega32p datasheet
// 2. pin configuration for in/out
// 3. read/write from pins
// 4. introduction in electrical workbench equipments
//  4.1. presentation + utilization multimeter (measure R, Vd)
//  4.2. presentation + visualization on oscilloscope
//  4.3. presentation programmable power supply

// Components
// 2 LEDs + resistors
// 1 Push Button + resistor

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints

void setup() {
    // initialize GDB stub
    debug_init();
    DDRD |=(1<<2); //led0
    DDRD &= ~(1<<4);
    PORTD |= (1 << 4);
}

void loop() {

    if (!(PIND & (1 << 4)))
        PORTB |= (1 << 2);      
    else
        PORTB &= ~(1 << 2);
    delay(100);
}