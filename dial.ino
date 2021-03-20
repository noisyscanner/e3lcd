#define PIN_SW D8
#define PIN_A D6
#define PIN_B D7

#define CLICKS_PER_STEP  4

bool isFirstTime = true;
bool isChangingYear = false;
int nextYear = currentYear;

ESPRotary r = ESPRotary(PIN_A, PIN_B, CLICKS_PER_STEP, INITIAL_YEAR);
Button2 b = Button2(PIN_SW, INPUT_PULLUP);

void nextView() {
  currentView = static_cast<ViewType>((currentView + 1) % NUM_VIEWTYPES);
}

void prevView() {
  if (currentView == year) {
    currentView = static_cast<ViewType>(NUM_VIEWTYPES - 1); 
  } else {
    currentView = static_cast<ViewType>((currentView - 1) % NUM_VIEWTYPES); 
  }
}

//void rotate(ESPRotary& r) {
//  if (isChangingYear) {
//    currentYear = r.getPosition();
//    printYear();
//  }
//}

void showDirection(ESPRotary& r) {
  byte dir = r.getDirection();

  if (isChangingYear) {
    if (dir == RE_LEFT) {
      if (nextYear != minYear) {
        nextYear--;
      }
    } else {
      if (nextYear != maxYear) {
        nextYear++;
      }
    }
  } else {
    if (dir == RE_LEFT) {
      prevView();
    } else {
      nextView();
    }
  }

  render();
}

void click(Button2& b) {
  if (isFirstTime) {
    isFirstTime = false;
    return;
  }

  isChangingYear = !isChangingYear;
  if (!isChangingYear) {
    // Just selected a new year. Reload
    // If the same one was selected we just fetch latest data
    currentYear = nextYear;
    currentView = year;
    fetchStats();
  }
  render();
}

void longPress(Button2& b) {
  toggleBacklight();
}

void setupRotaryEncoder() {
//  r.setChangedHandler(rotate);

  b.setClickHandler(click);
  b.setLongClickHandler(longPress);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);
}

void rotaryLoop() {
  b.loop();
  r.loop();
}
