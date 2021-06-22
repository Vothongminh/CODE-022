//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <Wire.h>
#include <LiquidCrystal_I2C.h>    //https://drive.google.com/file/d/1lpJyuODmZXfi7wwBM2B79BqBIBmBfanS/view?usp=sharing
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define start 8
#define stopp 7
#define CTHT 6
#include <Servo.h>
Servo myservo;
int pos = 0;
boolean demStart = 0;
int counter = 0;
//.....................................................
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(start, INPUT_PULLUP);
  pinMode(stopp, INPUT_PULLUP);
  pinMode(CTHT, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("Times:");
  myservo.write(pos);
}
//.....................................................
void loop() {
  if ((digitalRead(CTHT) == 0) && (digitalRead(start) == 0)) {
    demStart = 1;
    servo();
  }
  if (digitalRead(stopp) == 0) {
    demStart = 0;
    counter = 0;
    lcd.setCursor(7, 1);
    lcd.print("         ");
  }
  lcd.setCursor(7, 1);
  lcd.print(counter);
  if ((demStart == 1) && (digitalRead(CTHT) == 0)) {
    servo();
  }
}
//.......................................................
void servo() {
  counter++;
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(5);  // tốc độ
    if (digitalRead(stopp) == 0) {
      demStart = 0;
      counter = 0;
      lcd.setCursor(7, 1);
      lcd.print("         ");
    }
  }
  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(5);  // tốc độ
    if (digitalRead(stopp) == 0) {
      demStart = 0;
      counter = 0;
      lcd.setCursor(7, 1);
      lcd.print("         ");
    }
  }
}
