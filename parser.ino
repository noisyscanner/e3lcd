#include <ArduinoJson.h>

StaticJsonDocument<400> doc;

void parse(const char content[]) {
  deserializeJson(doc, content);

  isDst = doc["dst"] == true;
}
