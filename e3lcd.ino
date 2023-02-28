#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPRotary.h>
#include <Button2.h>

bool isDst = false;

String dateStr;
int hours;
int mins;
int seconds;
int currentMillis;

const char* ssid = "BT-NFASJW";
const char* password = "rRK6pfkCGMR3nf";

const char* host = "worldtimeapi.org";
const int httpsPort = 443;
String url = "/api/timezone/Europe/London";

// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;

void setup() {
  Serial.begin(9600);

  currentMillis = millis();

  setupRotaryEncoder();
  setupLcd();

  connectToWifi();
  fetchStats();
  updateLcd();
}

void loop() {
  rotaryLoop();

  int nextMillis = millis();
  if (nextMillis - currentMillis >= 1000) { // 1 second
    seconds++;
    currentMillis = nextMillis;

    if (seconds >= 60) {
      seconds = 0;
      mins++;
    }

    if (mins == 60) {
      mins = 0;
      hours++;
    }

    if (hours == 24) {
      hours = 0;
      // Refresh at midnight to ensure accuracy
      fetchStats();
    }

    updateLcd();
  }
}
