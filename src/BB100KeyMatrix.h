#ifndef _BB100KeyMatrix_
#define _BB100KeyMatrix_
#include "KeyLayout.h"
#include "KeyMatrix.h"

static const  pinNumber columnPins[] = {
  7,
  8,
  9,
  10,
  11,
  12,
  26,
  13,
  14,
  15
};

static const  pinNumber rowPins[] = {
  2,
  3,
  4,
  5,
  6,
  1
};


const keymap_t BB100Map[] = {
// these are arranged by the pin rows and columns
// pin col 0
    {  0, KEY_MINUS },
    {  1, KEY_BACKSLASH },
    {  2, KEY_QUOTE },
    {  3, MODIFIERKEY_RIGHT_SHIFT },
    {  4, KEY_RIGHT_FN },
    {  5, KEY_EQUAL },
// col 1
    {  6, KEY_0 },
    {  7, KEY_P },
    {  8, KEY_SEMICOLON },
    {  9, KEY_SLASH },
    { 10, KEY_RIGHT_BRACE },
    { 11, KEY_LEFT_FN },
// col 2
    { 12, KEY_9 },
    { 13, KEY_O },
    { 14, KEY_L },
    { 15, KEY_PERIOD },
    { 16, KEY_LEFT_BRACE },
    { 17, KEY_Z },
// col 3
    { 18, KEY_8 },
    { 19, KEY_I },
    { 20, KEY_K },
    { 21, KEY_COMMA },
    { 22, MODIFIERKEY_RIGHT_GUI },
    { 23, MODIFIERKEY_LEFT_SHIFT },
// col 4
    { 24, KEY_7 },
    { 25, KEY_U },
    { 26, KEY_J },
    { 27, KEY_M },
    { 28, KEY_SPACE },
    { 29, KEY_A },
// col 5
    { 30, KEY_6 },
    { 31, KEY_Y },
    { 32, KEY_H },
    { 33, KEY_N },
    { 34, KEY_ENTER },
    { 35, MODIFIERKEY_LEFT_CTRL },
// col 6
    { 36, KEY_5 },
    { 37, KEY_T },
    { 38, KEY_G },
    { 39, KEY_B },
    { 40, MODIFIERKEY_LEFT_GUI },
    { 41, KEY_Q },
// col 7
    { 42, KEY_4 },
    { 43, KEY_R },
    { 44, KEY_F },
    { 45, KEY_V },
    { 46, KEY_BACKSPACE },
    { 47, KEY_TAB },
// col 8
    { 48, KEY_3 },
    { 49, KEY_E },
    { 50, KEY_D },
    { 51, KEY_C },
    { 52, MODIFIERKEY_LEFT_ALT },
    { 53, KEY_1 },
// col 9
    { 54, KEY_2 },
    { 55, KEY_W },
    { 56, KEY_S },
    { 57, KEY_X },
    { 58, KEY_ESC },
    { 59, KEY_TILDE },
 // end of table marker
    { NO_KEY, NO_CODE }
};


const keylayout_t BB100Layout[] = {
// code, x, y, w, h
// these are arranged by the visual layout of the keys
// left of display
// visual column 0
  {59, 0,  0, 1, 1},
  {47, 0,  1, 1, 1},
  {35, 0,  2, 1, 1},
  {23, 0,  3, 1, 1},
  {11, 0,  4, 1, 1},
// column 1
  {53, 1,  0, 1, 1},
  {41, 1,  1, 1, 1},
  {29, 1,  2, 1, 1},
  {17, 1,  3, 1, 1},
  {5,  1,  4, 1, 1},
// column 2
  {54,  2,  0, 1, 1},
  {55,  2,  1, 1, 1},
  {56,  2,  2, 1, 1},
  {57,  2,  3, 1, 1},
  {58,  2,  4, 1, 1},
// column 3
  {48,  3,  0, 1, 1},
  {49,  3,  1, 1, 1},
  {50,  3,  2, 1, 1},
  {51,  3,  3, 1, 1},
  {52,  3,  4, 1, 1},
// column 4
  {42,  4,  0, 1, 1},
  {43,  4,  1, 1, 1},
  {44,  4,  2, 1, 1},
  {45,  4,  3, 1, 1},
  {46,  4,  4, 1, 1},
// column 5
  {36,  5,  0, 1, 1},
  {37,  5,  1, 1, 1},
  {38,  5,  2, 1, 1},
  {39,  5,  3, 1, 1},
  {40,  5,  4, 1, 1},
// column 6
  {30,  6,  0, 1, 1},
  {31,  6,  1, 1, 1},
  {32,  6,  2, 1, 1},
  {33,  6,  3, 1, 1},
  {34,  6,  4, 1, 1},
// column 7
  {24, 7,  0, 1, 1},
  {25, 7,  1, 1, 1},
  {26, 7,  2, 1, 1},
  {27, 7,  3, 1, 1},
  {28, 7,  4, 1, 1},
// column 8
  {18, 8,  0, 1, 1},
  {19, 8,  1, 1, 1},
  {20, 8,  2, 1, 1},
  {21, 8,  3, 1, 1},
  {22, 8,  4, 1, 1},
// column 9
  {12,  9,  0, 1, 1},
  {13,  9,  1, 1, 1},
  {14,  9,  2, 1, 1},
  {15,  9,  3, 1, 1},
  {16,  9,  4, 1, 1},
// column 10
  {6, 10,  0, 1, 1},
  {7, 10,  1, 1, 1},
  {8, 10,  2, 1, 1},
  {9, 10,  3, 1, 1},
  {10,10,  4, 1, 1},
// column 11
  {0, 11,  0, 1, 1},
  {1, 11,  1, 1, 1},
  {2, 11,  2, 1, 1},
  {3, 11,  3, 1, 1},
  {4, 11,  4, 1, 1},

  // end of table marker
  { NO_KEY, 0, 0, 0, 0 }
};

class BB100KeyMatrix : public GPIOKeyMatrix {
  public:
    BB100KeyMatrix() : GPIOKeyMatrix(BB100Layout, BB100Map, 6, 10, rowPins, columnPins) {};
    const char* name() { return "BB100"; }
  private:

};

#endif
