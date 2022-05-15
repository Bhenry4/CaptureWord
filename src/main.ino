/*The main file for CaptureWord
Gets words from EEPROM and runs the game loop*/

#include <LiquidCrystal_I2C.h> //I2C library
#define LCD LiquidCrystal_I2C
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3
LCD lcd(0x27, 16, 2); // Creates an object named "lcd" of the "LiquidCrystal_I2C" class (I2C address, columns, rows)

void timerISR()
{
} // TODO: Add button handlers

void nextISR() {}

String getWord()
{
    int indexLocation = EEPROM.read(0);
    int index = EEPROM.read(indexLocation);
    int nextIndex = EEPROM.read(indexLocation + 1);
    String word;

    for (int i = index; i < nextIndex; ++i)
    {
        word = word + EEPROM.read(i);
    }
    word = word + "\0";
    EEPROM.update(0, 1); // "Update" writes only if there is a difference; Until I get more words
}

String leftPad(String word)
{
    int wordLength = sizeof(word) - 1;
    int pad = (16 - wordLength) / 2;
    String paddedWord;
    for (int i = 0; i <= pad; ++i)
    {
        paddedWord += ' ';
    }
    paddedWord += word;
    return paddedWord;
}

void setup()
{ // put your setup code here, to run once:
    pinMode(timerButton, INPUT);
    // pinMode(nextButton, INPUT);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(2, 0); // Moves print location to column, row (starting from 0)
    lcd.print("CaptureWord");
    lcd.setCursor(2, 1);
    lcd.print("Press timer");

    while (!digitalRead(timerButton))
    {
    }
}

void loop()
{ // put your main code here, to run repeatedly:
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING);
    // attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);

    String word = getWord();
    word = leftPad(word);
    lcd.clear();
    lcd.home();
    lcd.print(word);
    while (true)
    {
    }
}
