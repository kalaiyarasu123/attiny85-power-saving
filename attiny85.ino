#include <avr/sleep.h>
#include <avr/interrupt.h>
const int Pushbutton = 3; // may be any sensor in digital
const int statusLED = 2;

void setup() {
    pinMode(Pushbutton, INPUT); 
    digitalWrite(Pushbutton, HIGH);
    pinMode(statusLED, OUTPUT);
}
void sleep() {
    GIMSK |= _BV(PCIE);                     // Refer ATTINY85 datasheet to Enable Pin Changes Interrupt
    PCMSK |= _BV(PCINT3);                   // Sleect PB3 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // This Command will Turn ADC off to reduces power consumption
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement
    sleep_enable();                         // This will set the sleep enable bit in ATTINY register (SE BIT)
    sei();                                  // This Enable the interrupts for understand if any interrupts occur
    sleep_cpu();                            // Go to sleep mode , waiting for interrupt
    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin while entered
    sleep_disable();                        // software Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC mode on
    sei();                                  // Enable  all interrupts
    } // sleep
ISR(PCINT0_vect) {
    // This is called when the interrupt occurs, but I don't need to do anything in it
    }

void loop() {                         // Continuous loop
    
    digitalWrite(statusLED, HIGH);  // LED starts glow
    delay(1000);                   // Delay for 1 Sec
    digitalWrite(statusLED, LOW); // LED off
    delay(1000);                 // Delay for 1 Sec
 
    sleep();                    //go to sleep funcetion calling
    }
