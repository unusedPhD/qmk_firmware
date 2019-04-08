#include "jd45.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _MOVE 6
#define _ADJUST 16

// Keycodes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT
};

enum macro_keycodes {
  KC_ALT_TAB,
  KC_CMD_TAB,
  KC_CTL_TAB,
  KC_CMD_SLSH,
  KC_AG_FIND,
  KC_AG_AGAIN,
  KC_AG_UNDO,
  KC_AG_CUT,
  KC_AG_COPY,
  KC_AG_PASTE,
  KC_AG_DESK_L,
  KC_AG_DESK_R,
  KC_AG_TAB_C,
  KC_AG_TAB_N,
  KC_AG_TAB_R,
};

// Fillers to make layering more clear
#define _______ KC_TRNS

// Custom macros
#define CTL_ESC CTL_T(KC_ESC)      // Tap for Esc, hold for Ctrl
#define SFT_ENT SFT_T(KC_ENT)      // Tap for Enter, hold for Shift
#define TC_BKSP LT(_MOVE, KC_BSPC)
#define TC_SP   LT(_MOVE, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Qwerty
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp | Bksp |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * | Ctrl/Esc |   A  |   S  |  D   |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |     '      |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  Sft/Ent  |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |  Ctrl  |  Alt  |  Cmd  | Lower | TC/Bcks  | TC/Space |  Raise  |  Cmd   |  Alt   |   Ctrl   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
[_QWERTY] = KEYMAP_JD45(
    KC_TAB ,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_DEL , KC_BSPC,
    CTL_ESC ,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,    KC_QUOT     ,
    KC_LSFT  ,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,    SFT_ENT    ,
    KC_LCTL  ,  KC_LALT  ,  KC_LGUI  ,   LOWER   ,   TC_BKSP ,   TC_SP   ,    RAISE  ,  KC_RGUI  ,  KC_RALT  , KC_RCTL),


/* Lower
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   `     |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |  \   |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |  =   |      |      |             |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   _  |   +  |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * | Brite  |       |       |       |          |          |         | Vol Dw | Vol Up |   Mute   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
[_LOWER] = KEYMAP_JD45(
    KC_GRV ,KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, _______, KC_BSLS ,
    _______ ,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_MINS, KC_EQL, _______, _______,    _______       ,
    _______  ,  KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_UNDS,  KC_PLUS, _______, _______,    _______    ,
    BACKLIT  ,    _______,    _______,    _______,  _______  ,  _______  ,    _______,    KC_VOLD,    KC_VOLU, KC_MUTE),


/* Raise
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   0     |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |   \  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |   4  |   5  |   6  |   .  |   +  |      |      |      |      |      |            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |   7  |   8  |   9  |   0  |   -  |      |      |      |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * | Brite  |       |       |       |          |          |         |  Prev  |  Play  |   Next   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
[_RAISE] = KEYMAP_JD45(
    KC_0   ,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, KC_BSLS,
    _______ ,   KC_4,    KC_5,    KC_6,  KC_DOT, KC_PLUS, _______, _______, _______, _______, _______,    _______     ,
    _______  ,   KC_7,    KC_8,    KC_9,    KC_0, KC_MINS, _______, _______, _______, _______, _______,    _______    ,
    BACKLIT  ,    _______,    _______,    _______,  _______  ,  _______  ,    _______,    KC_MPRV,  KC_MPLY , KC_MNXT),


/* brackets and navigation
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |      |  {   |   }  |      |      |      |      |      |      |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |      |      |  (   |   )  |      | Left | Down | Up   |Right |      |            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |  [   |   ]  |      | Home | PgDw |PgUp  | End  |      |           |
 * |-----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
[_MOVE] = KEYMAP_JD45(
   _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______, _______, _______, _______,
    _______ ,_______, _______, KC_LPRN, KC_RPRN, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,_______,     _______     ,
    _______  ,_______, _______, KC_LBRC, KC_RBRC, _______, KC_HOME,  KC_PGDN, KC_PGUP, KC_END, _______,    _______    ,
    _______  ,    _______,    _______,    _______, _______   , _______   ,    _______,    _______,    _______, _______),

/* Adjust (Lower + Raise)
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |      |      |      |      |      |      |      |      |      |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |      |      |      |      |      |      |      |      |      |      |            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      |      |     |       |      |      |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |  Reset   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
[_ADJUST] = KEYMAP_JD45(
    _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______ ,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______     ,
    _______  ,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______    ,
    _______  ,    _______,    _______,    _______,  _______  ,  _______  ,    _______,    _______,    _______,  RESET)


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}

