#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define CTL_ESC  CTL_T(KC_ESC)       // Tap for Esc, hold for Ctrl
#define SFT_ENT  SFT_T(KC_ENT)       // Tap for Enter, hold for Shift
#define SFT_BSP  SFT_T(KC_BSPC)      // Tap for Enter, hold for Shift
#define SP_DW    LT(_LOWER, KC_SPC)  // Tap for space, hold for lower layer
#define SP_UP    LT(_RAISE, KC_SPC)  // Tap for space, hold for raise layer
#define LFT_MVE  LT(_MOVE, KC_LEFT)  // Tap for space, hold for raise layer

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define _QWERTY 0
#define _NUMPAD 1
#define _LOWER 2
#define _RAISE 3
#define _MOVE 4
#define _ADJUST 16

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  NPAD,
  LOWER,
  RAISE,
  MOVE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC},
  {CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,       KC_J,    KC_K,    KC_L, KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,       KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_ENT},
  {NPAD,    KC_LCTL, KC_LGUI, KC_LALT, SP_DW,   SFT_BSP, SFT_ENT,   SP_UP, LFT_MVE, KC_DOWN,   KC_UP, KC_RGHT}
},

[_NUMPAD] = {
  {_______, _______, _______, _______, _______, _______,    KC_7,    KC_8,    KC_9, _______, KC_PSLS, KC_BSPC},
  {_______, _______, _______, _______, _______, _______,    KC_4,    KC_5,    KC_6, _______, KC_PAST, KC_DEL},
  {_______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, _______, KC_PMNS, KC_PEQL},
  {_______, _______, _______, _______, _______, _______,    KC_0,    KC_0,  KC_DOT, _______, KC_PPLS, KC_PENT}
},

[_LOWER] = {
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL},
  {KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS},
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU}
},

[_RAISE] = {
  {KC_GRV,  KC_TILD, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, _______, _______, _______, _______, _______, KC_DEL},
  {KC_BSLS, KC_PIPE, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_QUOT},
  {_______, _______, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU}
},

[_MOVE] = {
  {_______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP},
  {_______, _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  KC_PGDN},
  {_______, _______, _______, _______, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_UP,   XXXXXXX},
  {_______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_RGHT}
}

};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = SONG(STARTUP_SOUND);
float tone_qwerty[][2]  = SONG(QWERTY_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);
float tone_dvorak[][2]  = SONG(DVORAK_SOUND);
float music_scale[][2]  = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case NPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case MOVE:
      if (record->event.pressed) {
        layer_on(_MOVE);
      } else {
        layer_off(_MOVE);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE
void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}
#endif
