/*The main file for CaptureWord
Gets words from EEPROM and runs the game loop*/

#include <LiquidCrystal_I2C.h> //I2C library
#define LCD LiquidCrystal_I2C
#include <EEPROM.h> //Memory library

#define timerButton 2
#define nextButton 3
LCD lcd(0x27, 16, 2); // Creates an object named "lcd" of the "LiquidCrystal_I2C" class (I2C address, columns, rows)

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

void printCenteredWord(char word[], int wordLength) {
    int pad = 16/wordLength; //Fix This
    char paddedWord[pad+wordLength];
    for (int i = 0; i <= pad; ++i){
        paddedWord[i] = ' ';
    }
    for (int i = 0; i <= wordLength; i++){
        paddedWord[i+pad] = word[i];
    }
    lcd.print(paddedWord);
}

void timerLoop() {
    attachInterrupt(digitalPinToInterrupt(timerButton), timerISR, RISING);
    attachInterrupt(digitalPinToInterrupt(nextButton), nextISR, RISING);

    char word[getWordLength()];
    getWord(word);
    printCenteredWord(word, sizeof(word)-1);
}

void setup()
{ // put your setup code here, to run once:
    pinMode(timerButton, INPUT);
    pinMode(nextButton, INPUT);

    lcd.init();
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
    timerLoop();
}
