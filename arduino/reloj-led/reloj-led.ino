#include <Adafruit_NeoPixel.h>
#include "RTClib.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     14
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  20
// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 200

#define UNA 19
#define DOS 8
#define TRES 17
#define CUATRO 10
#define CINCO 15
#define SEIS 12
#define SIETE 13
#define OCHO 14
#define NUEVE 11
#define DIEZ 16
#define ONCE 9
#define DOCE 18
#define Y 7
#define MENOS 6
#define CINCOMIN 5
#define DIEZMIN 4
#define CUARTO 3
#define VEINTE 2
#define VEINTICINCO 1
#define MEDIA 0


RTC_DS3231 rtc;

int onoffpin = 15;
int button = 9;
int state = LOW;

int hours = 0, minutes = 0, seconds = 0;

DateTime now;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(onoffpin, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
  digitalWrite(onoffpin, HIGH);


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2019, 12, 4, 21, 44, 0));
  }
  strip.clear();
}

void loop() {
  now = rtc.now();
  hours = now.hour();
  minutes = now.minute();
  seconds = now.second();
  state = digitalRead(button);

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
  

  if(seconds > 30){
    minutes++;
  }
  if(minutes % 5 > 3){
    minutes++;
  }
  if(state == LOW){ 
    if(minutes > 2 && minutes < 33)
      strip.setPixelColor(Y, strip.Color(255, 0, 5));
    if(minutes > 32 && minutes < 58){
      strip.setPixelColor(MENOS, strip.Color(255, 0, 5));
      hours++;
    }

    if(minutes > 2 && minutes < 7 || minutes > 51 && minutes < 57)
      strip.setPixelColor(CINCOMIN, strip.Color(255, 0, 5));
    if(minutes > 6 && minutes < 12 || minutes > 46 && minutes < 52){
      strip.setPixelColor(DIEZMIN, strip.Color(255, 0, 5));
    }
    if(minutes > 11 && minutes < 17 || minutes > 41 && minutes < 47){
      strip.setPixelColor(CUARTO, strip.Color(255, 0, 5));
    }
    if(minutes > 16 && minutes < 22 || minutes > 36 && minutes < 42){
      strip.setPixelColor(VEINTE, strip.Color(255, 0, 5));
    }
    if(minutes > 21 && minutes < 27 || minutes > 31 && minutes < 37){
      strip.setPixelColor(VEINTICINCO, strip.Color(255, 0, 5));
    }
    if(minutes > 26 && minutes < 32){
      strip.setPixelColor(MEDIA, strip.Color(255, 0, 5));
    }
    if(hours > 12){
      hours = hours - 12;
    }
    Serial.println(hours);
    switch(hours){
    case 0:
      strip.setPixelColor(DOCE, strip.Color(255, 0, 5));
      break;
    case 1:
      strip.setPixelColor(UNA, strip.Color(255, 0, 5));
      break;
    case 2:
      strip.setPixelColor(DOS, strip.Color(255, 0, 5));
      break;
    case 3:
      strip.setPixelColor(TRES, strip.Color(255, 0, 5));
      break;
    case 4:
      strip.setPixelColor(CUATRO, strip.Color(255, 0, 5));
      break;
    case 5:
      strip.setPixelColor(CINCO, strip.Color(255, 0, 5));
      break;
    case 6:
      strip.setPixelColor(SEIS, strip.Color(255, 0, 5));
      break;
    case 7:
      strip.setPixelColor(SIETE, strip.Color(255, 0, 5));
      break;
    case 8:
      strip.setPixelColor(OCHO, strip.Color(255, 0, 5));
      break;
    case 9:
      strip.setPixelColor(NUEVE, strip.Color(255, 0, 5));
      break;
    case 10:
      strip.setPixelColor(DIEZ, strip.Color(255, 0, 5));
      break;
    case 11:
      strip.setPixelColor(ONCE, strip.Color(255, 0, 5));
      break;
    case 12:
      strip.setPixelColor(DOCE, strip.Color(255, 0, 5));
      break;
    default:
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        strip.show();
        delay(50);
      }
      break;
    }
    strip.show();
  }else{
    for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(10);
    }
  }
  //Serial.print("Temperature: ");
  //Serial.print(rtc.getTemperature());
  //Serial.println(" C");
  delay(500);
}
