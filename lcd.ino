#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ADDRESS = 0x27;
const byte COLS = 16;
const byte ROWS = 2;

LiquidCrystal_I2C lcd(ADDRESS, COLS, ROWS);

void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void printTop(const char* str) {
  lcd.setCursor(0, 0);
  lcd.print(str);
  lcdPad(str);
}

void printBot(const char* str) {
  lcd.setCursor(0, 1);
  lcd.print(str);
  lcdPad(str);
}

void lcdPad(const char* str) {
  for (int i = sizeof(str); i < COLS; i++) {
    lcd.print(" ");
  }
}

String getTitlePrefixForView(ViewType view) {
  switch (view) {
    case year:
      return "Scrapped";
    case organic:
      return "Organic";
    default:
      return "";
  }
}

String getTitleForView(ViewType view) {
  return getTitlePrefixForView(view) + " " + String(currentYear);
}
