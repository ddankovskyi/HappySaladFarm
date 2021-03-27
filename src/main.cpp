#include <Arduino.h>
#include "RTClib.h"
#include <Wire.h>

int lightOnH = 9;
int lightOffH = 23;

int lightPin = 10;



RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void showTime();
void updateStatus();
void initLight();

bool isLightOn = false;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set clock time
  //showTime();

  initLight();
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

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
  DateTime future (now + TimeSpan(7,12,30,6));

  Serial.print(" now + 7d + 12h + 30m + 6s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();

  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  Serial.println();
  delay(3000);
}
