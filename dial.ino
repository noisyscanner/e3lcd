#define PIN_SW D8
#define PIN_A D6
#define PIN_B D7

#define CLICKS_PER_STEP  4

// Rotary disabled as there is no use for it right now
// Click to toggle backlight
Button2 b = Button2(PIN_SW, INPUT_PULLUP);

void click(Button2& b) {
  toggleBacklight();
}

void setupRotaryEncoder() {
  b.setClickHandler(click);
}

void rotaryLoop() {
  b.loop();
}
