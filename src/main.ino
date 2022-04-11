/*The main file for CaptureWord
Gets words from EEPROM and runs the game loop*/

#include <LiquidCrystal_I2C.h> //I2C library
#define LCD LiquidCrystal_I2C
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3

void timerISR() {} // TODO: Add button handlers

void nextISR() {}

int getWordLength()
{
    int location = EEPROM.read(0); // First value in EEPROM is the location of the index of the current word
    int index = EEPROM.read(location);
    int nextIndex = EEPROM.read(location + 1);
    return nextIndex - index;
}

void getWord(char word[])
{
    int location = EEPROM.read(0);
    int index = EEPROM.read(location);
    int nextIndex = EEPROM.read(location + 1);
    int length = nextIndex - index;

    for (int i = index; i < length; i++)
    {
        word[i] = EEPROM.read(i);
    }
    EEPROM.update(location, location + 1); // "Update" writes only if there is a difference
}

LCD lcd(0x27, 16, 2); // Creates an object named "lcd" of the "LiquidCrystal_I2C" class (I2C address, columns, rows)

void setup()
{ // put your setup code here, to run once:
    pinMode(timerButton, INPUT);
    pinMode(nextButton, INPUT);

    lcd.init();
    lcd.backlight();     // Turns backlight on
    lcd.setCursor(2, 0); // Moves print location to column, row (starting from 0)
    lcd.print("CaptureWord");
    lcd.setCursor(2, 1);
    lcd.print("Press timer");
}

void loop()
{ // put your main code here, to run repeatedly:
    while (!digitalRead(timerButton))
    {
    }
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING);
    attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);
}
