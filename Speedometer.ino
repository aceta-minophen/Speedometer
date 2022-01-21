#include <LiquidCrystal.h>

const int reedSwitch = 8;
int flag = 0;

int Contrast = 100;
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

//Changing variables
int lastState = LOW;
int currentState;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

//Calculating variables
float circ = 65.973; //inches
float speedi; //inches/sec
float speedm; //kmph... speedm = 0.0914 speedi


void setup() {
  analogWrite(6, Contrast);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Team Yantriki");

  lcd.setCursor(0,1);
  lcd.print("MAC0061");
  delay(2000);

  Serial.begin(9600);
  pinMode(reedSwitch, INPUT);


  //led blink program
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  currentState = digitalRead(reedSwitch);

  if(lastState == LOW && currentState == HIGH){
    pressedTime = millis();
  } else if(lastState == HIGH && currentState == LOW){
    releasedTime = millis();
  }

  long pressDuration = releasedTime - pressedTime;

  speedm = -(circ*91.44)/pressDuration;

  if(pressDuration < 0){
    if(flag == 0){
      Serial.println(speedm);
      lcd.begin(16,2);
      lcd.setCursor(0,1);
      lcd.print(speedm);
      lcd.print(" kmph");
      lcd.print("                 ");
      flag = 1;
    } else if(flag == 1){
      Serial.println(speedm);
      lcd.setCursor(0,1);
      lcd.print(speedm);
      lcd.print(" kmph");
      lcd.print("                 ");
      flag = 0;
    }
  }


  lastState = currentState;

}
