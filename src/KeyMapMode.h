#include "RazzleMode.h"
#include "BBLCKeyMatrix.h"
extern BBLCKeyMatrix keyMatrix;

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

class KeyMapMode : public RazzleMode {
  public:
    virtual const char* name() { return "KeyMap"; }
    virtual void draw(RazzleMatrix* frame);
    virtual framerate_t fps() { return 30; }
    virtual bool canRun() { return true; }
    virtual bool dither() { return false; }

  private:

};

KeyMapMode theKeyMapMode;

// here we go
void KeyMapMode::draw(RazzleMatrix* frame) {
  CRGB color;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (keyMatrix.switchIsDown(i)) {
      color = CRGB::White;
    } else {
      keycode_t c = keyMatrix.getCode(i);
      color = keyColor(c);
    }
    frame->drawPixelCRGB(keyMatrix.getKeyX(i),keyMatrix.getKeyY(i),color);
  }
}
