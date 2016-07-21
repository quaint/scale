#include <Adafruit_Thermal.h>
#include <LiquidCrystal.h>
#include "SoftwareSerial.h"
#include "wisnie.h"
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//used pins: 0,1,2,3,4,5,6,7,8,9,10
//unused pins: 11,12,13

#define TX_PIN 3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 2 // Arduino receive   GREEN WIRE   labeled TX on printer

#define PIN 11
#define NUMPIXELS 75

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

RTC_DS1307 rtc;

char incoming;
char outbound[78];
int i = 0;
int afterBegining = 0;
int afterEnd = 0;

int lcdKey = 0;
int adcKeyIn = 0;
int trailers[] = {0, 2200, 2400, 2380, 2320, 3000};
int selectedTrailer = 0;
const int trailersCount = 5;
int buttonPushed = btnNONE;
boolean printHeader = true;

unsigned long total = 0;

const int DISPLAY_WIDTH = 15;
const int DIGIT_WIDTH = 3;
const int DIGIT_HEIGHT = 5;
const int POWER =  50;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t COLOR_0 = pixels.Color(0, 0, 0);
const uint32_t COLOR_1 = pixels.Color(POWER, 0, 0);
const uint32_t COLOR_2 = pixels.Color(0, POWER, 0);
const uint32_t COLOR_3 = pixels.Color(0, 0, POWER);
const uint32_t COLOR_4 = pixels.Color(POWER, POWER, POWER);
const uint32_t COLOR_5 = pixels.Color(0, POWER, 0);

String lastReadWeight = "0";
String lastReadNumber = "0";

void setup() {
  Serial.begin(9600);
  mySerial.begin(19200);
  printer.begin();
  lcd.begin(16, 2);              // start the library
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  //  lcd.setCursor(0, 0);
  //  lcd.print(F("Waga przyczepy")); // print a simple message
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
}

void loop() {
  processLcdButtons();
  while (Serial.available() > 0) {
    incoming = Serial.read();
    if (i > 76) {
      i = 0;
    }
    if (incoming == 2) {
      afterBegining = 1;
      i = 0;
    }
    if (incoming == 3) {
      afterEnd = 1;
    }
    outbound[i] = incoming;
    i++;
    if (afterBegining == 1 && afterEnd == 1) {
      outbound[77] = '\0';
      afterBegining = 0;
      afterEnd = 0;
      processOutput();
    }
  }
}
