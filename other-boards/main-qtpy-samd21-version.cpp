/*--------------------------------------------------------------------------------------------*/
/*                                     John W. Mulholland                                     */
/*                                          2/8/2022                                          */
/*--------------------------------------------------------------------------------------------*/


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x27,20,4);
signed short minutes, seconds;
int djtimer = 15;
char timeline[16];

void setup() {
  Serial.begin(115200);
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
  while (analogRead(A2) <= 1000);
  lcd.clear();
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
}
void DJTimerSettings() {
  if (analogRead(A0) >= 1023) {
    delay(200);
    lcd.clear();
    djtimer = djtimer + 5;
    minutes = 0;
    seconds = 0;
    lcd.backlight();
    }
  if (analogRead(A1) >= 1023) {
    delay(200);
    lcd.clear();
    djtimer = djtimer - 5;
    minutes = 0;
    seconds = 0;
    lcd.backlight();
  }
  if (analogRead(A2) >= 1023 and minutes >= djtimer ) {
    delay(200);
    lcd.clear();
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
void mainDJtimer() {
  DJTimerSettings();
  lcd.setCursor(4,0);
  lcd.print("EVOLVE Music");
  lcd.setCursor(4,1);
  lcd.print("DJ Timer: ");
  lcd.print(djtimer);
  lcd.setCursor(7, 2);
  sprintf(timeline,"%.2dmins", minutes);
  lcd.print(timeline);
  delay(1000);
  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes ++;
  }
  if (minutes >= djtimer) {
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("NEXT DJ!!");
    lcd.noBacklight();
  }
  if (seconds <= djtimer) {
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("NEXT DJ!!");
    lcd.backlight();
  }
}

void loop() {
  mainDJtimer();
}
