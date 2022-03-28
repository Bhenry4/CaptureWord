#include <Adafruit_LiquidCrystal.h> //I2C library
#define LC Adafruit_LiquidCrystal
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3

LC lcd(0); // Creates an object named "lcd" of the "Adafruit_LiquidCrytal" class

void setup()
{                                                                          // put your setup code here, to run once:
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING); // ISR = Interrupt Service Routine
    attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);

    lcd.begin(16, 2); // 16x2 lcd screen
}

void loop()
{ // put your main code here, to run repeatedly:
}

void timerISR() {} // TODO: Add button handlers

void nextISR() {}

char *getWord()
{
    int address = rand() % 10 /*placeholder until I get word list*/;
    int index = EEPROM.read(address);
    int nextIndex = EEPROM.read(address + 1);
    char word[nextIndex - index];

    for (int i = index; i < nextIndex - index; i++)
    {
        word[i] = EEPROM.read(i);
    }
    return word;
}
