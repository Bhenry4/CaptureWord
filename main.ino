#include <Wire.h> //I2C library (might use LiquidCrystal_I2C instead)
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3

void setup()
{                                                                          // put your setup code here, to run once:
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING); // ISR = Interrupt Service Routine
    attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);
}

void loop()
{ // put your main code here, to run repeatedly:
}

void timerISR() {}

void nextISR() {}

void displayText(char text[]) {} //TODO: Figure out I2C commands

char getWord() {
    int i = 0;//TODO: add code to find index
}