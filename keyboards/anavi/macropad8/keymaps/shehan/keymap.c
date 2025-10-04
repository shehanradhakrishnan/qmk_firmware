#include QMK_KEYBOARD_H

enum layers {
  _MAIN,
  _APPS,
  _MEDIA,
  _VLC,
  _LINUX,
  _FN,
};

enum custom_keycodes {     
    STEAM = SAFE_RANGE,     // SAFE_RANGE prevents it from using a clashing keycode
    VLC,
    FIREFOX,
    VSCODE,
    WARFRAME,
    EVERCRISIS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case STEAM:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "steam://open/library" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
        case VLC:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "vlc" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
        case FIREFOX:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "firefox" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
        case VSCODE:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "code" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
        case WARFRAME:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "steam://rungameid/230410" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
        case EVERCRISIS:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(500) "steam://rungameid/2484110" SS_DELAY(500) SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            break;
    }
    return true;
}

// #define _MAIN 0
// #define _APPS 1
// #define _MEDIA 2
// #define _VLC 3
// #define _LINUX 4
// #define _FN 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _MAIN: (Base Layer) Default Layer
   * ,-------------------------------------------------------,
   * | Ctl+Sft+ESC |    Calc.    |    My PC    |   TO(_FN)   |
   * |-------------------------------------------------------|
   * |  TO(_APPS)  | TO(_MEDIA)  |  TO(_VLC)   | TO(_LINUX)  |
   * `-------------------------------------------------------`
   */
  [_MAIN] = LAYOUT_ortho_2x4(
     RCS(KC_ESC), KC_CALC,    KC_MYCM,  TO(_FN),
     TO(_APPS),   TO(_MEDIA), TO(_VLC), TO(_FN)
  ),

  /* Keymap _APPS: Commonly Used Apps
   * ,-------------------------------------------------------,
   * |   Firefox   | MediaPlayer |  VLC Player |   VS Code   |
   * |-------------------------------------------------------|
   * |  TO(_MAIN)  |    Steam    |  Warframe   | Ever Crisis |
   * `-------------------------------------------------------`
   */
  [_APPS] = LAYOUT_ortho_2x4(
     FIREFOX,   KC_MSEL, VLC,      VSCODE,
     TO(_MAIN), STEAM,   WARFRAME, EVERCRISIS
  ),

  /* Keymap _MEDIA: MS Music Player
   * ,-------------------------------------------------------,
   * | MediaPlayer |    Prev.    |    Play     |    Next     |
   * |-------------------------------------------------------|
   * |  TO(_MAIN)  |    Mute     |   Shuffle   |   Repeat    |
   * `-------------------------------------------------------`
   */
  [_MEDIA] = LAYOUT_ortho_2x4(
     KC_MSEL,   KC_MPRV, KC_MPLY,    KC_MNXT,
     TO(_MAIN), KC_MUTE, LCTL(KC_H), LCTL(KC_T)
  ),

  /* Keymap _VLC: VLC Media Player
   * ,-------------------------------------------------------,
   * |  VLC Player |    Prev.    |    Play     |    Next     |
   * |-------------------------------------------------------|
   * |  TO(_MAIN)  |    Mute     |  Prv. Chap  |  Nxt. Chap  |
   * `-------------------------------------------------------`
   */
  [_VLC] = LAYOUT_ortho_2x4(
     VLC,       KC_MPRV, KC_MPLY,    KC_MNXT,
     TO(_MAIN), KC_MUTE, LSFT(KC_P), LSFT(KC_N)
  ),

  /* Keymap _LINUX: For Fedora OS
   * ,-------------------------------------------------------,
   * |     F1      |     F2      |     F3      |     F4      |
   * |-------------------------------------------------------|
   * |  TO(_MAIN)  |     F5      |     F7      |     F8      |
   * `-------------------------------------------------------`
   */
  // [_LINUX] = LAYOUT_ortho_2x4(
  //    KC_F1,     KC_F2, KC_F3, KC_F4,
  //    TO(_MAIN), KC_F5, KC_F7, KC_F8
  // ),

  /* Keymap _FN: Backlight & RGB Function Layer
   * ,-------------------------------------------------------,
   * |   RGB Tog.  |  RGB Mode + |  RGB Mode - |  Chg Color  |
   * |-------------------------------------------------------|
   * |  TO(_MAIN)  |   BL. Tog.  |   BL. Inc.  |   BL. Dec.  |
   * `-------------------------------------------------------`
   */
  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG,   RGB_MOD, RGB_RMOD, RGB_HUI,
     TO(_MAIN), BL_TOGG, BL_UP,    BL_DOWN
  )
};

#ifdef OLED_ENABLE
/* Don't Rotate Screen */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      oled_write_ln_P(PSTR("Main"), false);
      break;
    case _APPS:
      oled_write_ln_P(PSTR("Programs"), false);
      break;
    case _MEDIA:
      oled_write_ln_P(PSTR("Media"), false);
      break;
    case _VLC:
      oled_write_ln_P(PSTR("VLC"), false);
      break;
    case _LINUX:
      oled_write_ln_P(PSTR("Fedora"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("RGB"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  /* Don't Have Num Pad or Use Scroll Lock
  oled_write_P(PSTR("Num Lock: "), false);
  oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Scroll Lock: "), false);
  oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
  */
  oled_write_P(PSTR("Caps Lock: "), false);
  oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Backlit: "), false);
  oled_write_ln_P(is_backlight_enabled() ? PSTR("On") : PSTR("Off"), false);
#ifdef RGBLIGHT_ENABLE
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
#endif
    return false;
}
#endif
