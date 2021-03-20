#include <LiquidCrystal_I2C.h>

const byte ADDRESS = 0x27;
const byte COLS = 16;
const byte ROWS = 2;

bool isOn = true;

LiquidCrystal_I2C lcd(ADDRESS, COLS, ROWS);

void setupLcd() {
  lcd.begin();
  turnOn();
}

void turnOn() {
  isOn = true;
  lcd.backlight();
}

void turnOff() {
  isOn = false;
  lcd.backlight();
}

void updateBacklight() {
  if (isOn) {
    lcd.noBacklight();
  } else {
    lcd.backlight();
  }
}

void toggleBacklight() {
  isOn = !isOn;
  updateBacklight();
}

void printTop(const char* str) {
  lcd.setCursor(0, 0);
  lcd.print(str);
  lcdPad();
}

void printBot(const char* str) {
  lcd.setCursor(0, 1);
  lcd.print(str);
  lcdPad();
}

void lcdPad() {
  for (int i = 0; i <= COLS; i++) {
    lcd.print(" ");
  }
}

String getTitlePrefixForView() {
  switch (currentView) {
    case year:
      return "Scrapped";
    case organic:
      return "Organic";
    case fb:
      return "Facebook";
    case wordOfMouth:
      return "Word of Mth";
    case repeat:
      return "Repeat";
    default:
      return "";
  }
}

String formatTime() {
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", hours, mins);
  return String(timeStr);
}

String getTitleForView() {
  return getTitlePrefixForView() + " " + String(currentYear);
}

void updateLcd() {
  if (currentView == theTime) {
    printTop("");
    printBot(formatTime().c_str());
    return;
  }

  printTop(getTitleForView().c_str());
  printBot(String(getValueForView()).c_str());
}

void printYear() {
  printTop(String(nextYear).c_str());
  printBot("");
}

void printLoading() {
  printTop("    E3 AUTOS");
  printBot("  Loading......");
}

void render() {
  if (isChangingYear) {
    printYear();
  } else {
    updateLcd();
  }
}
