#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "version.h"
#include "sendstring_german_mac_iso.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
    RGB_SLD = ZSA_SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_voyager(
        UG_TOGG, KC_NO,        KC_NO,        KC_NO,        KC_NO,           KC_NO, /* │ */ KC_NO, KC_MPRV,       KC_MPLY,      KC_MNXT,      KC_VOLD,      KC_VOLU,
        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,            KC_T,  /* │ */ DE_Z,  KC_U,          KC_I,         KC_O,         KC_NO,        KC_NO,
        KC_ESC,  LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),    KC_G,  /* │ */ KC_H,  LGUI_T(KC_J),  LALT_T(KC_K), LCTL_T(KC_L), LSFT_T(KC_P), KC_ENT,
        KC_NO,   DE_Y,         KC_X,         KC_C,         KC_V,            KC_B,  /* │ */ KC_B,  KC_N,          KC_M,         KC_COMMA,     KC_DOT,       KC_NO,
                                                           LT(1, KC_SPACE), MO(3), /* │ */ KC_NO, LT(2, KC_BSPC)
    ),
    [1] = LAYOUT_voyager(
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* │ */ KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* │ */ KC_NO,   LCTL(DE_Y), LCTL(KC_U), KC_PGUP,    KC_NO,      KC_NO,
        KC_TRNS,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, /* │ */ KC_NO,   KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_NO,
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /* │ */ KC_NO,   LCTL(KC_E), LCTL(KC_D), KC_PGDN,    KC_NO,      KC_PGUP,
                                              KC_TRNS, KC_TRNS, /* │ */ KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_voyager(
        KC_NO, KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   /* │ */ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NUBS, S(KC_NUBS), KC_NO,   DE_SLSH, /* │ */ DE_BSLS, KC_NO,   DE_LBRC, DE_RBRC, KC_NO,   KC_NO,
        KC_NO, DE_UNDS, DE_EXLM, DE_QUES,    DE_EQL,  DE_QUOT, /* │ */ KC_GRV,  DE_LPRN, DE_LCBR, DE_RCBR, DE_RPRN, KC_NO,
        KC_NO, DE_PERC, DE_AMPR, DE_PIPE,    DE_DQUO, DE_GRV,  /* │ */ DE_DLR,  DE_HASH, DE_PLUS, DE_MINS, DE_ASTR, KC_NO,
                                             KC_TRNS, KC_LGUI, /* │ */ KC_NO,   KC_TRNS
    ),
    [3] = LAYOUT_voyager(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /* │ */ KC_NO,   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /* │ */ KC_NO,   DE_7,   DE_8,  DE_9,  KC_NO, KC_NO,
        KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   /* │ */ KC_NO,   DE_4,   DE_5,  DE_6,  DE_0,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   /* │ */ KC_NO,   DE_1,   DE_2,  DE_3,  KC_NO, KC_NO,
                                            KC_TRNS, KC_TRNS, /* │ */ KC_TRNS, KC_TRNS
    ),
};

const key_override_t *key_overrides[] = {
    // Option + o = ö
    &ko_make_basic(MOD_MASK_ALT, KC_O, DE_ODIA),
    // Option + u = ü
    &ko_make_basic(MOD_MASK_ALT, KC_U, DE_UDIA),
    // Option + a = ä
    &ko_make_basic(MOD_MASK_ALT, MT(MOD_LSFT, KC_A), DE_ADIA),
    // Option + s = ß
    &ko_make_basic(MOD_MASK_ALT, LCTL_T(KC_S), DE_SS),
	NULL
};

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_SPACE):
            return true;
        default:
            return false;
    }
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT:
        case MOD_LCTL:
        case MOD_LALT:
        case MOD_LGUI:
            return true;
        default:
            return false;
    }
}

bool achordion_chord(
    uint16_t tap_hold_keycode,
    keyrecord_t* tap_hold_record,
    uint16_t other_keycode,
    keyrecord_t* other_record
) {
    switch (tap_hold_keycode) {
        case LT(1, KC_SPACE):
            return achordion_opposite_hands(tap_hold_record, other_record);
        default:
            return true;
    }
}

uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode) {
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) { return 0; }

    const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if ((mod & MOD_LSFT) != 0 && next_keycode == KC_COMMA) { return 0; }
    if ((mod & MOD_LSFT) != 0 && next_keycode == KC_DOT) { return 0; }
    if ((mod & MOD_LSFT) != 0) { return 100; }

    return 220;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }

    return true;
}
