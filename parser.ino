#include <ArduinoJson.h>

StaticJsonDocument<400> doc;

void parse(const char content[]) {
  deserializeJson(doc, content);

  currentYear = doc["current_year"];
  minYear = doc["min_year"];
  maxYear = doc["max_year"];
}

int getValueForView() {
  switch (currentView) {
    case year:
      return doc["cars_this_year"];
    case organic:
      return doc["how_obtained_totals"]["ORGANIC"];
    case wordOfMouth:
      return doc["how_obtained_totals"]["WORD"];
    case fb:
      return doc["how_obtained_totals"]["FB"];
    case repeat:
      return doc["how_obtained_totals"]["REPEAT"];
    default:
      return 0;
  }
}
