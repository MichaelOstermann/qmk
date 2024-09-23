#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
    RGB_SLD = ML_SAFE_RANGE,
    ST_MACRO_0,
    ST_MACRO_1,
    ST_MACRO_2,
    ST_MACRO_3,
    MAC_LOCK,
};

// Copy pasted from Oryx.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_voyager(
        MAC_LOCK,       RGB_TOG,        KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_AUDIO_MUTE,  KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           DE_Z,           KC_U,           KC_I,           KC_O,           KC_NO,          KC_NO,
        KC_ESCAPE,      MT(MOD_LSFT, KC_A),MT(MOD_LCTL, KC_S),MT(MOD_LALT, KC_D),MT(MOD_LGUI, KC_F),KC_G,                                           KC_H,           MT(MOD_RGUI, KC_J),MT(MOD_RALT, KC_K),MT(MOD_RCTL, KC_L),MT(MOD_RSFT, KC_P),KC_ENTER,
        KC_NO,          DE_Y,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_B,           KC_N,           KC_M,           CW_TOGG,        QK_AUTOCORRECT_TOGGLE,          KC_NO,
                                                        LT(1,KC_SPACE), KC_TRANSPARENT,                                 KC_HYPR,        LT(2,KC_BSPC)
    ),
    [1] = LAYOUT_voyager(
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          ST_MACRO_0,     ST_MACRO_1,     ST_MACRO_2,     ST_MACRO_3,     KC_NO,
        KC_TRANSPARENT, KC_LEFT_SHIFT,  KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    KC_NO,                                          KC_NO,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT,
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          LCTL(KC_D),     LCTL(KC_F),     LCTL(KC_B),     LCTL(KC_U),     KC_NO,
                                                        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [2] = LAYOUT_voyager(
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
        KC_NO,          DE_GRV,         DE_QUOT,        DE_PIPE,        DE_QST,         DE_SLSH,                                        DE_BSLS,        DE_EXLM,        DE_AMPR,        DE_DQOT,        DE_PERC,        KC_NO,
        DE_CIRC,        DE_LESS,        DE_LBRC,        DE_LCBR,        DE_LPRN,        DE_PLUS,                                        DE_EQL,         DE_RPRN,        DE_RCBR,        DE_RBRC,        DE_MORE,        DE_DLR,
        KC_NO,          DE_ASTR,        DE_MINS,        KC_COMMA,       KC_DOT,         DE_HASH,                                        DE_AT,          DE_COLN,        DE_SCLN,        DE_UNDS,        DE_TILD,        KC_NO,
                                                        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_TRANSPARENT
    ),
    [3] = LAYOUT_voyager(
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_7,           KC_8,           KC_9,           KC_NO,          KC_NO,
        KC_TRANSPARENT, KC_LEFT_SHIFT,  KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    KC_NO,                                          KC_NO,          KC_4,           KC_5,           KC_6,           KC_0,           KC_TRANSPARENT,
        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_1,           KC_2,           KC_3,           KC_NO,          KC_NO,
                                                        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    ),
};

const key_override_t **key_overrides = (const key_override_t *[]){
    // Option + o = ö
    &ko_make_basic(MOD_MASK_ALT, KC_O, DE_OE),
    // Option + u = ü
    &ko_make_basic(MOD_MASK_ALT, KC_U, DE_UE),
    // Option + a = ä
    &ko_make_basic(MOD_MASK_ALT, MT(MOD_LSFT, KC_A), DE_AE),
    // Option + s = ß
    &ko_make_basic(MOD_MASK_ALT, MT(MOD_LCTL, KC_S), DE_SS),
	NULL
};

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Long-pressing space and releasing results with nothing happening by default (just switches to my nav layer and back),
        // feels bad when I'm using neovim since that's my <leader> key - trigger space upon release in this case.
        case LT(1, KC_SPACE):
            return true;
        default:
            return false;
    }
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        // Without these, I'd have to wait ~1s before I can do something like cmd + click.
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
        // Space is my <leader> key in neovim, with most secondary keys situated on my left side (eg. <leader>e, <leader>w, etc.).
        // With this setting I can be a bit sloppier here, since the layer switch only happens when I hold space and press
        // something on my right side (I don't have any bindings for my left side).
        // Without this, I frequently press space for a little bit too long, layer 1 activates and then im probably hitting a KC_NO key which does nothing.
        case LT(1,KC_SPACE):
            return achordion_opposite_hands(tap_hold_record, other_record);

        default:
            return true;
    }
}

// Intent is to make accidental ctrl/cmd shortcuts less likely to happen, when going fast (cmd+q hurts a lot).
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode) {
    // Disable streak detection on space/backspace, otherwise when I'm going fast things get eg. deleted.
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) { return 0; }

    // Shorter timeout for shifts, I'd have to go *really* fast to consider shift a mispress.
    const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if ((mod & MOD_LSFT) != 0) { return 100; }

    return 220;
}

void matrix_scan_user(void) {
    achordion_task();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    // Copy pasted from Oryx.
    switch (keycode) {
        case ST_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_W)) SS_DELAY(100) SS_TAP(X_H));
            }
            break;
        case ST_MACRO_1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_W)) SS_DELAY(100) SS_TAP(X_J));
            }
            break;
        case ST_MACRO_2:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_W)) SS_DELAY(100) SS_TAP(X_K));
            }
            break;
        case ST_MACRO_3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_W)) SS_DELAY(100) SS_TAP(X_L));
            }
            break;
        case MAC_LOCK:
            HCS(0x19E);
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }

    return true;
}
