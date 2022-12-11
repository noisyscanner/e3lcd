#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPRotary.h>
#include <Button2.h>

#define INITIAL_YEAR 2021
#define DST          true

// TODO: Clock view, parse Date header from response
enum ViewType { year, organic, wordOfMouth, fb, repeat, theTime, NUM_VIEWTYPES };
ViewType currentView = year;
int currentYear = INITIAL_YEAR;
int minYear = 2015;
int maxYear = 2021;
int hours;
int mins;
int currentMillis;

const char* ssid = "BT-NFASJW";
const char* password = "rRK6pfkCGMR3nf";

const char* host = "e3autos.co.uk";
const int httpsPort = 443;
String url = "/api/stats";

// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;

void setup() {
  Serial.begin(9600);

  currentMillis = millis();

  setupRotaryEncoder();
  setupLcd();

  connectToWifi();
  fetchStats();
  render();
}

void loop() {
  rotaryLoop();

  int nextMillis = millis();
  if (nextMillis - currentMillis >= 60000) { // 1 min
    mins++;
    if (mins == 60) {
      mins = 00;
      hours++;
    }

    if (hours == 24) {
      hours = 0;
    }

    Serial.print(hours);
    Serial.print(" ");
    Serial.print(mins);

    updateLcd();
    currentMillis = nextMillis;
  }
}
