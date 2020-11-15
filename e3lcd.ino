#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

enum ViewType { year, organic, wordOfMouth, fb, repeat };
ViewType currentView = organic;
int currentYear = 2020;

const char* ssid = "1 Broncksea Road 2G";
const char* password = "lekxmgmw";

const char* host = "e3autos.co.uk";
const int httpsPort = 443;
String url = "/api/stats";

// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;

void connectToWifi() {
//  Serial.print("connecting to ");
//  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //  Serial.println("");
  //  Serial.println("WiFi connected");
  //  Serial.println("IP address: ");
  //  Serial.println(WiFi.localIP());

  // CBA to validate certs
  client.setInsecure();
}

void fetchStats() {
  if (!client.connect(host, httpsPort)) {
    printTop("connection");
    printBot("failed");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: Arduino\r\n" +
               "Connection: close\r\n\r\n");

  String line;

  // Pass headers
  while (client.connected()) {
    line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String content;

  while (client.available()) {
    content = client.readString();
  }

  parse(content.c_str());
}

void updateLcd() {
  printTop(getTitleForView(currentView).c_str());
  printBot(String(getValueForView(currentView)).c_str());
}

void setup() {
  setupLcd();
  printTop("Loading");
  printBot("..............");

  Serial.begin(115200);

  connectToWifi();
  // loadCurrentYear(); // to use as max for dial
  fetchStats();
  updateLcd();
}

void loop() {
  // Detect dial turning left or right to inc/dec the year
  // Update to show chosen year as twisting is happening
  // Delay 500ms and then load stats for that year

  // Detect button press
  // Cycle through stats already loaded into memory
}
