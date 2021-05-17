#include <Arduino.h>
#include "RTClib.h"
#include <Wire.h>

int lightOnH = 9;   // hour of turning light on
int lightOffH = 23; // hour of turning light off

int lightPin = 2;
int humidifierPin = 3;

void updateHumidifier();

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void showTime();
void updateStatus();
void initLight();

bool isLightOn = false;

int humOnTimeH = lightOnH;
int humOffTimeH = lightOnH + 4;
bool isHumOn = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Hello salad3");
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set clock time
  showTime();

  initLight();
  pinMode(humidifierPin, OUTPUT);

  updateStatus();
  Serial.println("light on ");
  Serial.println(isLightOn);
  Serial.println("humidifier on ");
  Serial.println(isHumOn);
  // put your setup code here, to run once:
}

void loop () {
  updateStatus();
//
}

void updateStatus(){
  DateTime now = rtc.now();

  isLightOn = now.hour() >= lightOnH && now.hour() < lightOffH;
  //isLightOn = now.minute()%2 <= 0;
  digitalWrite(lightPin, isLightOn);
  updateHumidifier();
  delay(3000);
}



void updateHumidifier()
{
  if(!isLightOn){
    if(isHumOn) {
      isHumOn = false;
      digitalWrite(humidifierPin, isHumOn);
    }
    return;
  }
  DateTime now = rtc.now();

  if(!isHumOn && now.hour() >= humOnTimeH){
    humOffTimeH = now.hour() + 4;
    if(humOffTimeH > lightOffH) humOffTimeH = lightOffH;
    isHumOn = true;
    digitalWrite(humidifierPin, isHumOn);
    return;
  }

  if(isHumOn && now.hour() >= humOffTimeH){
    humOnTimeH = now.hour() + 1;
    if(humOnTimeH > lightOffH) humOnTimeH = lightOnH;
    isHumOn = false;
    digitalWrite(humidifierPin, isHumOn);
    return;
  }

}


void initLight(){
  pinMode(lightPin, OUTPUT);
}

void showTime(){
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(3000);
}
