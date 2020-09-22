#ifndef _FunctionOverlay_

const keyoverlay_t functionOverlay[] = {
// row 0
    { KEY_TILDE, KEY_F11 },
    { KEY_1, KEY_F1 },
    { KEY_2, KEY_F2 },
    { KEY_3, KEY_F3 },
    { KEY_4, KEY_F4 },
    { KEY_5, KEY_F5 },

    { KEY_6, KEY_F6 },
    { KEY_7, KEY_F7 },
    { KEY_8, KEY_F8 },
    { KEY_9, KEY_F9 },
    { KEY_0, KEY_F10 },
    { KEY_MINUS, KEY_F12 },

    { KEY_Q, KEY_FIRST_MACRO + 0 },
    { KEY_W, KEY_FIRST_MACRO + 1 },
    { KEY_E, KEY_FIRST_MACRO + 2 },
    { KEY_R, KEY_FIRST_MACRO + 3 },
    { KEY_A, KEY_FIRST_MACRO + 4 },
    { KEY_S, KEY_FIRST_MACRO + 5 },
    { KEY_D, KEY_FIRST_MACRO + 6 },
    { KEY_F, KEY_FIRST_MACRO + 7 },
    { KEY_Z, KEY_FIRST_MACRO + 8 },
    { KEY_X, KEY_FIRST_MACRO + 9 },
    { KEY_C, KEY_FIRST_MACRO + 10 },
    { KEY_V, KEY_FIRST_MACRO + 11 },

    { KEY_Y, KEY_MEDIA_PREV_TRACK },
    { KEY_U, KEY_MEDIA_PLAY_PAUSE },
    { KEY_I, KEY_MEDIA_NEXT_TRACK },
    { KEY_O, KEY_MEDIA_MUTE },
    { KEY_P, KEY_MEDIA_VOLUME_DEC },
    { KEY_BACKSLASH, KEY_MEDIA_VOLUME_INC },
    { KEY_QUOTE, KEY_MEDIA_EJECT },

    { KEY_LEFT_FN, KEY_LEFT_FN },
    { KEY_RIGHT_FN, KEY_RIGHT_FN },
    { MODIFIERKEY_RIGHT_SHIFT, MODIFIERKEY_RIGHT_SHIFT },
    { MODIFIERKEY_LEFT_SHIFT, MODIFIERKEY_LEFT_SHIFT },
    { KEY_ESC, KEY_ESC },

    { KEY_H, KEY_LEFT },
    { KEY_J, KEY_UP },
    { KEY_K, KEY_DOWN },
    { KEY_L, KEY_RIGHT },

    { KEY_N, KEY_MOUSE_MOVE_LEFT },
    { KEY_M, KEY_MOUSE_MOVE_UP },
    { KEY_COMMA, KEY_MOUSE_MOVE_DOWN },
    { KEY_PERIOD, KEY_MOUSE_MOVE_RIGHT },
    { KEY_ENTER, KEY_MOUSE_BUTTON_LEFT },

    { MODIFIERKEY_RIGHT_GUI, KEY_MOUSE_BUTTON_MIDDLE },
    { KEY_SPACE, KEY_MOUSE_BUTTON_RIGHT },
    { KEY_LEFT_BRACE, KEY_MOUSE_BUTTON_BACK },
    { KEY_RIGHT_BRACE, KEY_MOUSE_BUTTON_FORWARD },
    { KEY_UP, KEY_MOUSE_SCROLL_UP },
    { KEY_DOWN, KEY_MOUSE_SCROLL_DOWN },
    { KEY_LEFT, KEY_MOUSE_SCROLL_LEFT },
    { KEY_RIGHT, KEY_MOUSE_SCROLL_RIGHT },

    // end of table marker
    { NO_CODE, NO_CODE }  // replace the second value with ANY_CODE to make overlay transparent
};

const keyoverlay_t functionShiftOverlay[] = {
    { KEY_H, KEY_HOME },
    { KEY_J, KEY_PAGE_UP },
    { KEY_K, KEY_PAGE_DOWN },
    { KEY_L, KEY_END },
    { NO_CODE, NO_CODE }  // replace the second value with ANY_CODE to make overlay transparent
};

#endif