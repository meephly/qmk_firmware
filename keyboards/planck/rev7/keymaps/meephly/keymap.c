#include QMK_KEYBOARD_H

bool     is_alt_tab_active = false; // Super ALT TAB
uint16_t alt_tab_timer     = 0;     // Super ALT TAB

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    ALT_STAB,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case ALT_STAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer. For alt tab
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0]  = LAYOUT_ortho_4x12(
        KC_TAB,         KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,
        LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,        KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,   KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL,        KC_LGUI, KC_LALT, MO(4), MO(1), KC_SPC, KC_BSPC, KC_ENT, KC_DEL,  KC_MUTE, KC_MPLY, KC_ENT
    ),
    [1]  = LAYOUT_ortho_4x12(
        KC_TAB,         KC_F2,         KC_HOME, KC_UP,   KC_END,  KC_NO,         KC_AT,   KC_CIRC, KC_LBRC, KC_RBRC, KC_NO,   KC_GRV,
        LCTL_T(KC_ESC), LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_RGHT), KC_ASTR, KC_MINS, KC_LPRN, KC_RPRN, KC_EXLM, KC_BSLS,
        KC_LSFT,        KC_NO,         KC_NO,   KC_NO,   TG(2),   TG(3),         KC_HASH, KC_EQL,  KC_DLR,  KC_AMPR, KC_PERC, KC_VOLU,
        KC_LCTL,        KC_LGUI,       KC_LALT, KC_NO,   KC_NO,   KC_SPC,        KC_BSPC, KC_ENT,  KC_DEL,  KC_MUTE, KC_MPLY, KC_VOLD
    ),
    [2]  = LAYOUT_ortho_4x12(
        KC_TAB,         KC_NO,   KC_WH_U, KC_MS_U, KC_WH_D, KC_NO,   KC_NO,   KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_NO,
        LCTL_T(KC_ESC), KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, KC_NO,   KC_F5,   KC_F6,   KC_F7,  KC_F8,  KC_NO,
        KC_LSFT,        KC_NO,   KC_NO,   KC_NO,   TG(2),   KC_NO,   KC_NO,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_NO,
        KC_LCTL,        KC_LGUI, KC_LALT, KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_ENT,  KC_DEL,  KC_NO,  KC_NO,  KC_NO
    ),
    [3]  = LAYOUT_ortho_4x12(
        KC_TAB,  KC_NO,         LCAG(KC_UP),   LGUI(KC_UP),   LCAG(KC_DOWN), KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        TG(3),   LCAG(KC_LEFT), LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), LCAG(KC_RGHT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO,         KC_NO,         KC_NO,         KC_NO,         TG(3),         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LGUI,       KC_LALT,       KC_NO,         KC_NO,         KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [4]  = LAYOUT_ortho_4x12(
        KC_TAB,       KC_NO,   LALT(KC_F4), KC_NO,    KC_NO,   KC_NO,  KC_NUM,  KC_7,    KC_8,  KC_9,    KC_MINS, KC_PSCR,
        LALT(KC_SPC), KC_NO,   KC_NO,       ALT_STAB, ALT_TAB, KC_NO,  KC_NO,   KC_4,    KC_5,  KC_6,    KC_PLUS, KC_NO,
        KC_LSFT,      KC_F5,   KC_F6,       KC_F7,    KC_F8,   KC_NO,  KC_NO,   KC_1,    KC_2,  KC_3,    KC_EQL,  KC_ENT,
        KC_LCTL,      KC_LGUI, KC_LALT,     KC_NO,    KC_NO,   KC_SPC, KC_BSPC, KC_0,    MO(5), KC_NO,   KC_NO,   KC_NO
    ),
    [5]  = LAYOUT_ortho_4x12(TG(6), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
    [6]  = LAYOUT_ortho_4x12(
        TG(6), QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO,
        KC_NO, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
