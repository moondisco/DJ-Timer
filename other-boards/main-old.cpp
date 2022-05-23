#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <millisDelay.h>
millisDelay SecondsDelay;
millisDelay DJTimerLCD;
millisDelay DJTimerLCD2;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x27,20,4);
signed short minutes, seconds;
int djtimer = 15;
char timeline[16];

void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("EVOLVE Music");
  lcd.setCursor(6, 1);
  lcd.print("DJ Timer");
  lcd.setCursor(9,2);
  lcd.print("by");
  lcd.setCursor(5,3);
  lcd.print("Moon Disco");
  while (analogRead(A3) <= 1000);
  lcd.clear();
  SecondsDelay.start(1000);
  DJTimerLCD.start(1000);
  DJTimerLCD2.start(1000);
}
void DJTimerSettings() {
  if (analogRead(A0) >= 1023 ) {
    delay(100);
    lcd.clear();
    djtimer = djtimer + 5;
    minutes = 0;
    seconds = 0;
    lcd.backlight();
    }
  if (analogRead(A1) >= 1023 ) {
    delay(100);
    lcd.clear();
    djtimer = djtimer - 5;
    minutes = 0;
    seconds = 0;
    lcd.backlight();
    }

  if (djtimer == 35){
    djtimer = 60;
  }
  if (djtimer >= 61){
    djtimer = 1;
  }
  if (djtimer <= 1) {
    minutes = 0;
    seconds = 0;
    djtimer = 15;
  }
}
void ResetTime() {
  if (analogRead(A2) >= 900 ) {
    lcd.clear();
    minutes = 0;
    seconds = 0;
    lcd.backlight();
  }
}
void loop() {
  DJTimerSettings();
  lcd.setCursor(4,0);
  lcd.print("EVOLVE Music");
  lcd.setCursor(4,1);
  lcd.print("DJ Timer: ");
  lcd.print(djtimer);
  if (SecondsDelay.justFinished()) {
      SecondsDelay.repeat();
      lcd.setCursor(7, 2);
      sprintf(timeline,"%.2dmins", minutes);
      lcd.print(timeline);
      seconds++;
      if (seconds == 60) {
        seconds = 0;
        minutes ++;
      }
      if (seconds >= djtimer){
        lcd.clear();
        if (DJTimerLCD.justFinished()){
          DJTimerLCD2.start(250);
          lcd.clear();
          lcd.setCursor(5, 2);
          lcd.print("NEXT DJ!!");
          lcd.noBacklight();
          ResetTime();
        }
        if (DJTimerLCD2.justFinished()){
          lcd.clear();
          DJTimerLCD.start(250);
          lcd.setCursor(5, 2);
          lcd.print("NEXT DJ!!");
          lcd.backlight();
          ResetTime();
        }
      }
    }
}
