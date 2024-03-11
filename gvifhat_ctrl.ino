/*
Project: RasPi GVIF Hat changeover switch
Replaces JK-FF
Target device: ATtiny 412, 1MHz, WDT off
Programmer: jtag2updi
Author: Csaba Toth, 10.03.2024
*/
#include <avr/io.h>
#include <stdio.h>


#define THRUPIN A6
#define RASPIN A7
#define BUTTON A1
#define debounceDelay 300

void setup() {

  pinMode(THRUPIN, OUTPUT);
  pinMode(RASPIN, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(RASPIN, LOW);
  digitalWrite(THRUPIN, HIGH);
  //EVSYS.ASYNCCH0 = EVSYS_ASYNCCH0_PORTA_PIN1_gc; // set up TCB0 event input to take event channel 0
  //EVSYS.ASYNCUSER0 = EVSYS_ASYNCUSER0_ASYNCCH0_gc; 
  //attachInterrupt(digitalPinToInterrupt(BUTTON), buttonInterrupt, FALLING);
  //TCB0.EVCTRL |= TCB_CAPTEI_bm ; // Capture Event Input Enable
  //TCB0.INTCTRL |= TCB_CAPT_bm ; // Capture Interrupt Enable
  //TCB0.CTRLA |= (1 << 0); // enable TCB0
  //sei();

} //setup

enum State {
  STATE_HIGH_LOW,
  STATE_LOW_HIGH
}; // enum

enum State currentState;

void loop() {

  int buttonState = digitalRead(BUTTON);
  if (buttonState == LOW) {
    switch (currentState) {
    case STATE_HIGH_LOW:
      digitalWrite(THRUPIN, HIGH);
      digitalWrite(RASPIN, LOW);
      delay(debounceDelay);
      do {buttonState = digitalRead(BUTTON); }
        while  (buttonState == LOW); 
      currentState = STATE_LOW_HIGH;
      break;

    case STATE_LOW_HIGH:
      digitalWrite(THRUPIN, LOW);
      digitalWrite(RASPIN, HIGH);
      delay(debounceDelay);
      do {buttonState = digitalRead(BUTTON); }
        while  (buttonState == LOW); 
      currentState = STATE_HIGH_LOW;
      break;
    } // switch
  }

} // loop


/*
void buttonInterrupt(){



} // buttonInterrupt


ISR (TCB0_INT_vect) {
  TCB0.EVCTRL ^= TCB_EDGE_bm;
  buttonInterrupt();
}*/
