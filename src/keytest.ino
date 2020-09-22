#include <Adafruit_SleepyDog.h>

#include "Clock.h"
Clock clock;

#include "Console.h"
Console console;

#include "Commands/TeensyCommands.h"
#include "Commands/DateCommand.h"
#include "Commands/FPSCommand.h"
FPSCommand theFPSCommand;

#include "TypeCommand.h"

//#define FASTLED_ALLOW_INTERRUPTS 1
#include "FastLED.h"

#include "BB100KeyMatrix.h"
BB100KeyMatrix keyMatrix;

#include "FunctionOverlay.h"

#include "Adafruit_SSD1306.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class TestKeyEventQueue : public KeyEventQueue {
  public:
    TestKeyEventQueue(int maxEventHistory) : KeyEventQueue(maxEventHistory) {}
    virtual void processEvent(KeyEvent* key) override {
        if (key->pressed(KEY_LEFT_FN) || key->pressed(KEY_RIGHT_FN)) {
          if (keyMatrix.getOverlay() != functionOverlay) {
            console.debug("setting function layer\n");
            keyMatrix.setOverlay(functionOverlay);
          }
        } else if (
                   (key->released(KEY_LEFT_FN) || key->released(KEY_RIGHT_FN))  // released fn key
                  ) {
                console.debug("removing function layer\n");
                keyMatrix.setOverlay();
        }
      }

};

TestKeyEventQueue keyEvents(10);  // only remember 10 events, which isn't much

// note: this is [y][x]
const uint8_t BB100LEDGrid[5][12] = {
{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
{23,22,21,20,19,18,17,16,15,14,13,12},
{24,25,26,27,28,29,30,31,32,33,34,35},
{47,46,45,44,43,42,41,40,39,38,37,36},
{48,49,50,51,52,53,54,55,56,57,58,59}
};


struct keyCategoryColor {
  keycategory_t category;
  CRGB  color;
};

keyCategoryColor keyColors[] = {
  { KEY_CATEGORY_ALPHA, CRGB::Red },
  { KEY_CATEGORY_NUM, CRGB::Purple },
  { KEY_CATEGORY_PUNCTUATION, CRGB::Yellow },
  { KEY_CATEGORY_TEXT, CRGB::Green },
  { KEY_CATEGORY_MODIFIER, CRGB::Blue },

  { KEY_CATEGORY_FUNCTION, CRGB::Violet },
  { KEY_CATEGORY_CURSOR, CRGB::Turquoise },
  { KEY_CATEGORY_SYSTEM, CRGB::Chartreuse },
  { KEY_CATEGORY_MACRO, CRGB::Gray },
  { KEY_CATEGORY_MOUSE, CRGB::Lime },
  { KEY_CATEGORY_MEDIA, CRGB::Maroon },
  { KEY_CATEGORY_KEYPAD, CRGB::Brown },
  { KEY_CATEGORY_NONE, CRGB::Black }
};

CRGB keyColor(keycode_t c) {
  keycategory_t cat = getKeyCategory(c);
  int i = 0;
  do {
    if (keyColors[i].category == cat) {
      break;
    }
    i++;
  } while (keyColors[i].category != KEY_CATEGORY_NONE);
  return keyColors[i].color;
}

// this is the magic trick for printf to support float
//disabled for now
//asm(".global _printf_float");

#define NUM_LEDS 60
#define DATA_PIN 17
#define KEYBL_ENABLE_PIN 25
#define FPS 30
// power scale factor for low current leds 20mA / 5mA
#define WS2812CScale 4
#define MaxPowerInMilliamps 100

CRGB leds[NUM_LEDS];

void setup() {
  console.begin(&Serial,0);

//  console.debugf("Starting %dms watchdog\n",Watchdog.enable(4000));

  console.debugln("starting keyboard matrix");
  keyMatrix.begin(&keyEvents);

  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  set_max_power_in_volts_and_milliamps( 5, MaxPowerInMilliamps * WS2812CScale);

  pinMode(KEYBL_ENABLE_PIN, OUTPUT);

  digitalWrite(KEYBL_ENABLE_PIN, LOW);  // turn on the LED power


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    console.debugln("SSD1306 allocation failed");
  }

  // Show initial display buffer contents on the screen --  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println("hello");
  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();

}

void loop() {
  static millis_t lastMill = 0;

  console.idle();
//  Watchdog.reset();
  if (keyMatrix.update()) {
    // force an update if a key has transitioned
    lastMill = 0;
  }

  //  pass the keys through
  keyEvents.sendKeys();

  millis_t mill = clock.millis();
  if (mill > (lastMill + (1000/FPS))) {
//     static uint8_t hue = 0;
//    fill_rainbow (leds, NUM_LEDS, hue, 256/NUM_LEDS);
//       hue += 10;
      fill_solid(leds,NUM_LEDS, CRGB::Black);

      boolean keydown = false;
      CRGB color;
      for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t litkey = BB100LEDGrid[keyMatrix.getKeyY(i)][keyMatrix.getKeyX(i)];
        if (keyMatrix.switchIsDown(i)) {
          color = CRGB::White;
          if (getKeyCategory(keyMatrix.getCode(i)) != KEY_CATEGORY_MODIFIER) {
            keydown = true;
          }
        } else {
          keycode_t c = keyMatrix.getCode(i);
          color = keyColor(c);
        }
        fill_solid(leds+litkey, 1, color);
      }

      if (!keydown) {
//        fill_solid(leds,NUM_LEDS, CRGB::White);
        static uint8_t offset = 0;

        fill_solid(leds+offset, 1, CRGB::White);
        offset++;
        if (offset >= NUM_LEDS) { offset = 0; };
      }


      FastLED.show();
      lastMill = clock.millis();
      theFPSCommand.newFrame();
  }
}
