#include <LiquidCrystal_I2C.h> //I2C library
#define LCD LiquidCrystal_I2C
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3

LCD lcd(0x27, 16, 2); // Creates an object named "lcd" of the "Adafruit_LiquidCrytal" class (address, rows, columns)

void setup()
{                                                                          // put your setup code here, to run once:
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING); // ISR = Interrupt Service Routine
    attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);
}

void loop()
{ // put your main code here, to run repeatedly:
}

void timerISR() {} // TODO: Add button handlers

void nextISR() {}

int getWordLength()
{
    int location = EEPROM.read(0);
    int index = EEPROM.read(location);
    int nextIndex = EEPROM.read(location + 1);
    return nextIndex - index;
}

char *getWord(char word[])
{
    int location = EEPROM.read(0);
    int index = EEPROM.read(location);
    int nextIndex = EEPROM.read(location + 1);
    int size = nextIndex - index;

    for (int i = index; i < size; i++)
    {
        word[i] = EEPROM.read(i);
    }
    EEPROM.update(location, index + 1);
    return word;
}
