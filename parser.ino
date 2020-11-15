#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

void parse(const char content[]) {
  deserializeJson(doc, content);

//  Serial.println(getValueForView(year));
}

int getValueForView(ViewType view) {
  switch (view) {
    case year:
      return doc["cars_this_year"];
    case organic:
      return doc["how_obtained_totals"]["ORGANIC"];
    default:
      return 0;
  }
}
