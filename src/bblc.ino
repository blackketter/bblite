#include "Wire.h"
#ifdef HASDISPLAY
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

#include <RazzleMatrix.h>
#include <DefaultRazzleModes.h>

#ifdef CORE_TEENSY
#include "RamMonitor.h"
RamMonitor ram;
#endif

#include <Adafruit_SleepyDog.h>

#include "Clock.h"
Clock clock;

#include "Console.h"
Console console;

#ifdef CORE_TEENSY
#include "Commands/TeensyCommands.h"
#endif
#include "Commands/DateCommand.h"

#include "TypeCommand.h"

#include "keylayouts.h"
#include "BBLCKeyMatrix.h"
BBLCKeyMatrix keyMatrix;

#include "KeyOverlays.h"

class LCKeyEventQueue : public KeyEventQueue {
  public:
    LCKeyEventQueue(int maxEventHistory) : KeyEventQueue(maxEventHistory) {}
    virtual void processEvent(KeyEvent* key) override {
// TODO - use isPressed() to determine layer
        if (key->pressed(KEY_MOUSE)) {
          key->matrix()->setOverlay(mouseOverlay);
        } else if (key->released(KEY_MOUSE)) {
          key->matrix()->setOverlay();
        } if (key->pressed(KEY_LEFT_FN) || key->pressed(KEY_RIGHT_FN)) {
          if (key->matrix()->getOverlay() != functionOverlay) {
            console.debug("setting function layer\n");
            key->matrix()->setOverlay(functionOverlay);
          }
        } else if (key->released(KEY_LEFT_FN) || key->released(KEY_RIGHT_FN)) {

          console.debug("removing function layer\n");
          key->matrix()->setOverlay();
        }
      }

};

LCKeyEventQueue keyEvents(10);  // only remember 10 events, which isn't much


// this is the magic trick for printf to support float
//disabled for now
//asm(".global _printf_float");

#define NUM_LEDS 60
#define DATA_PIN 17
#define KEYBL_ENABLE_PIN 25
#define FPS 30
// power scale factor for low current leds 20mA / 5mA
#define WS2812CScale 4
#define MaxPowerInMilliamps 250


static RazzleMatrixConfig ledConfig {
  12,    // led_t width;
  5,     // led_t height;
  GRB,   // EOrder colorOrder;
  MaxPowerInMilliamps * WS2812CScale, // uint32_t powerSupplyMilliAmps;
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG, // uint8_t matrixType;
  {60}   // led_t segment[MAX_SEGMENTS];
};

RazzleMatrix* ledMatrix;

#include "KeyMapMode.h"

void setup() {

#ifdef CORE_TEENSY
  ram.initialize();
#endif

#ifdef ARDUINO_TEENSYLC
// TEENSYLC is memory constrained, no console log
  console.begin(&Serial,0);
#else
  console.begin(&Serial);
#endif
  Wire.begin();

  console.debugf("Starting %dms watchdog\n",Watchdog.enable(4000));

  console.debugln("starting keyboard matrix");
  keyMatrix.begin(&keyEvents);

  ledMatrix = setupLeds(&ledConfig);
  if (!ledMatrix) {
    console.debugln("Failed to set up led matrix");
  } else {
    ledMatrix->setBrightness(255, 255);
  }

  pinMode(KEYBL_ENABLE_PIN, OUTPUT);

  digitalWrite(KEYBL_ENABLE_PIN, LOW);  // turn on the LED power
#ifdef HASDISPLAY
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    console.debugln("SSD1306 allocation failed");
  } else {
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
#endif
}

void loop() {
#ifdef CORE_TEENSY
  ram.run();
#endif


  console.idle();
  if (keyMatrix.update()) {
    ledMatrix->setLEDMode(&theKeyMapMode);
  };
  Watchdog.reset();
  if (ledMatrix) {
    ledMatrix->idle();
  }

  //  pass the keys through
  keyEvents.sendKeys();
}
