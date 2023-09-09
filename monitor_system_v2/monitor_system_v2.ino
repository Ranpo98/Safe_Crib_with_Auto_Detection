#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <SoftwareSerial.h>
#include "text_printer.h"

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// pressure, sound, ultrasonic
#define CLIMBING_MASK 0x01
#define CRYING_MASK 0x02
#define MOVING_MASK 0x04

// The time gap between the previous notification and the current one
#define CRAWLING_GAP 300000
#define NC_GAP 5000

// The time out from the last message received
#define WAIT_MSG_TIME_OUT 3000

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
TextPrinter tp(tft, 2);
float p = 3.1415926;

// Pin definitions
const int TXD_of_hc05 = 3;
const int RXD_of_hc05 = 2;
const int buzzer_pin = 7;

// Variables related to messages
uint8_t status_code = 0;
unsigned long last_msg_time = 0;

// Varaibles to record the last time these notifications are made
unsigned long notif_timer[5] = {0, 0, 0, 0, 0};

// Variables related to Bluetooth
// pin3 to TXD of HC05
// pin2 to RXD of HC05
SoftwareSerial BT(TXD_of_hc05, RXD_of_hc05);

// Functions for alerts
void babyIsClimbing() {
  notif_timer[CLIMBING] = millis();
  digitalWrite(buzzer_pin, HIGH);
  tft.fillScreen(notif_bg_color[CLIMBING]);
  tp.setText("Your baby is climbing out of the crib.", 38);
  tp.setColorOfText(CLIMBING);
  tp.printText();
}

void babyIsCrying() {
  notif_timer[CRYING] = millis();
  digitalWrite(buzzer_pin, HIGH);
  tft.fillScreen(notif_bg_color[CRYING]);
  tp.setText("Your baby is crying.", 20);
  tp.setColorOfText(CRYING);
  tp.printText();
}

void babyIsCrawling() {
  unsigned long cur_time = millis();
  if (notif_timer[CRAWLING] + CRAWLING_GAP > cur_time) {
    return;
  }
  notif_timer[CRAWLING] = cur_time;
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
  tft.fillScreen(notif_bg_color[CRAWLING]);
  tp.setText("Your baby is crawling .", 23);
  tp.setColorOfText(CRAWLING);
  tp.printText();
}

void babyIsSafe() {
  digitalWrite(buzzer_pin, LOW);
  tft.fillScreen(notif_bg_color[SAFE]);
  tp.setText("Your baby is safe and quiet. :)", 31);
  tp.setColorOfText(SAFE);
  tp.printText();
}

void cribNotConnected() {
  unsigned long cur_time = millis();
  if (notif_timer[NC] + NC_GAP > cur_time) {
    return;
  }
  notif_timer[NC] = cur_time;
  digitalWrite(buzzer_pin, HIGH);
  delay(50);
  digitalWrite(buzzer_pin, LOW);
  tft.fillScreen(notif_bg_color[NC]);
  tp.setText("The crib signal is not found.", 29);
  tp.setColorOfText(NC);
  tp.printText();
}

// Set up and start the loop
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(buzzer_pin, OUTPUT);
  tft.init(170, 320);
  tft.fillScreen(ST77XX_GREEN);
  while (BT.available()) {
    BT.read();
  }
}

void loop() {
  unsigned long cur_time = millis();
  int avail_num = BT.available();
  if (avail_num == 0) {
    Serial.println("avail_num is 0");
  }
  
  if (cur_time > last_msg_time + WAIT_MSG_TIME_OUT) {
    Serial.println("time limit exceeded");
  }
  if (avail_num == 0 && cur_time > last_msg_time + WAIT_MSG_TIME_OUT) {
      cribNotConnected();
      return;
  }

  Serial.print("avail_num: ");
  Serial.println(avail_num);
  status_code = 0;
  while (--avail_num >= 0) {
    status_code |= (uint8_t) (BT.read());
  }
  // Serial.println("ever available");
  last_msg_time = cur_time;
  // Serial.println(status_code);
  if (status_code & CLIMBING_MASK) {
    babyIsClimbing();
  } else if (status_code & CRYING_MASK) {
    babyIsCrying();
  } else if (status_code & MOVING_MASK) {
    babyIsCrawling();
  } else {
    babyIsSafe();
  }
}
