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
#include "laboratory_types.h"

int cnt=0;
bool onOff=true;
void setup() {
    // initialize GDB stub
    debug_init();
    DDRD |=(1<<2); //led0
    DDRD |=(1<<7); //led1
    PORTD &= ~(1<<2);
    DDRD &= ~(1<<4);
    // TODO: 1. configure pin directions and turn off leds
}

void inline setLed0State(LedState state) {
    // TODO: 1. turn led0 on or off based on state
    if(state == OFF){
        PORTD |= (1<<2);    
    }
    else{
        PORTD &= ~(1<<2);
    }
}

// read button state
ButtonState inline readBtnState() {
    unsigned char btnIN = PIND & (1<<4);
    if(btnIN != 0)
        return ButtonState::PRESSED;
    else
       return ButtonState::NOT_PRESSED; 
    // TODO: 1. return if button is pressed
}

void inline setLed1State(LedState state) {
    
    if(state == OFF){
        PORTD |= (1<<7);    
    }
    else{
        PORTD &= ~(1<<7);
    }
    // TODO: 2. turn led1 on or off based on state
    
}

static void oscillatingLed() {
    // TODO: 2. toggle the led1 with the pattern: 500ms on, 200ms off
    cnt++;
    if(cnt<=5){
        setLed1State(ON);
    }
    else if(cnt>5){
        setLed1State(OFF);
    }
    if(cnt==7){
        cnt=0;
    }
    // TODO: 3. analyze on oscliisop the  led1 signal and measure the timing
}

// detect button press and toggle the led0 state
static void toggleLed(ButtonState btnState) {
    static bool lastState = ButtonState::NOT_PRESSED;
    static bool ledState = false;
    if ( lastState == ButtonState::NOT_PRESSED && 
            btnState == ButtonState::PRESSED ) {
        ledState = !ledState;
        setLed0State(ledState ? LedState::ON : LedState::OFF);
    }
    lastState = btnState;
}

void loop() {
    toggleLed(readBtnState());
    oscillatingLed();
    delay(100);
}