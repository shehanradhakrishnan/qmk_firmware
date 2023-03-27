#include QMK_KEYBOARD_H

enum layers {
  _MAIN,
  _MEDIA,
  _VLC,
  _WARFRAME,
  _FFXIV,
  _FN
};

// #define _MAIN 0
// #define _MEDIA 1
// #define _VLC 2
// #define _WARFRAME 3
// #define _FFXIV 4
// #define _FN 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _MAIN: (Base Layer) Default Layer
   * ,---------------------------,
   * |    TO(1)    | Ctl+Sft+ESC |
   * |---------------------------|
   * |    Ctl+C    |    Ctl+V    |
   * |---------------------------|
   * |    Win+D    |    Win+A    |
   * |---------------------------|
   * |  Sft+Win+S  | Win+Prt_Scr |
   * `---------------------------`
   */
  [_MAIN] = LAYOUT_ortho_2x4(
     RCS(KC_ESC), LCTL(KC_V), LGUI(KC_A), LGUI(KC_PSCR),
     TO(_MEDIA),  LCTL(KC_C), LGUI(KC_D), SGUI(KC_S)
  ),

  /* Keymap _MEDIA: Groove Music Layer
   * ,---------------------------,
   * |    TO(2)    |    Media    |
   * |---------------------------|
   * |    Prev.    |    Next     |
   * |---------------------------|
   * |    Play     |    Mute     |
   * |---------------------------|
   * |   Vol. D    |   Vol. U    |
   * `---------------------------`
   */
  [_MEDIA] = LAYOUT_ortho_2x4(
     KC_MSEL,  KC_MNXT, KC_MUTE, KC_F9,
     TO(_VLC), KC_MPRV, KC_MPLY, KC_F8
  ),

  /* Keymap _VLC: VLC Layer
   * ,---------------------------,
   * |    TO(2)    |    Calcu    |
   * |---------------------------|
   * |    Prev.    |    Next     |
   * |---------------------------|
   * |    Play     |    Mute     |
   * |---------------------------|
   * |   Vol. D    |   Vol. U    |
   * `---------------------------`
   */
  // Later change CALC to macro that opens VLC player using Win+R
  [_VLC] = LAYOUT_ortho_2x4(
     KC_CALC,       KC_MNXT, KC_M,    LCTL(KC_UP),
     TO(_WARFRAME), KC_MPRV, KC_MPLY, LCTL(KC_DOWN)
  ),

  /* Keymap _WARFRAME: For Warframe
   * ,---------------------------,
   * |    TO(3)    |     F1      |
   * |---------------------------|
   * |     F2      |     F3      |
   * |---------------------------|
   * |     F4      |     F5      |
   * |---------------------------|
   * |     F7      |     F8      |
   * `---------------------------`
   */
  [_WARFRAME] = LAYOUT_ortho_2x4(
     KC_F1,      KC_F3, KC_F5, KC_F8,
     TO(_FFXIV), KC_F2, KC_F4, KC_F7
  ),

  /* Keymap _FFXIV: For Final Fantasy 14 (Hotbar 2: 1-6 + 12)
   * ,---------------------------,
   * |    TO(4)    |    Ctl+`    |
   * |---------------------------|
   * |    Ctl+1    |    Ctl+2    |
   * |---------------------------|
   * |    Ctl+3    |    Ctl+4    |
   * |---------------------------|
   * |    Ctl+5    |    Ctl+6    |
   * `---------------------------`
   */
  [_FFXIV] = LAYOUT_ortho_2x4(
     LCTL(KC_GRV), LCTL(KC_2), LCTL(KC_4), LCTL(KC_6),
     TO(_FN)     , LCTL(KC_1), LCTL(KC_3), LCTL(KC_5)
  ),

  /* Keymap _FN: Backlight & RGB Function Layer
   * ,---------------------------,
   * |    TO(0)    |   RGB Tog.  |
   * |---------------------------|
   * |   BL. Tog.  |  RGB Mode + |
   * |---------------------------|
   * |   BL. Inc.  |  RGB Mode - |
   * |---------------------------|
   * |   BL. Dec.  |  Chg Color  |
   * `---------------------------`
   */
  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG,   RGB_MOD, RGB_RMOD, RGB_HUI,
     TO(_MAIN), BL_TOGG, BL_INC,  BL_DEC
  )
};

#ifdef OLED_ENABLE
/* Don't Rotate Screen
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}
*/

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      oled_write_ln_P(PSTR("Main"), false);
      break;
    case _MEDIA:
      oled_write_ln_P(PSTR("Media"), false);
      break;
    case _VLC:
      oled_write_ln_P(PSTR("VLC"), false);
      break;
    case _WARFRAME:
      oled_write_ln_P(PSTR("Warframe"), false);
      break;
    case _FFXIV:
      oled_write_ln_P(PSTR("FFXIV"), false);
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
