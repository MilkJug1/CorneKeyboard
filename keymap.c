/*

Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute
#define VIAL_KEYBOARD_UID {0x26, 0x1D, 0xDA, 0xB0, 0xF1, 0xB8, 0x87, 0x31}

// NOTE: I USE VIAL-QMK WITH MY KEYBOARD, EVERYTHING REGARDING TAP-DANCES IS
// THERE PLUS COMBOS
//

// This counts from an index of zero, plus this is how the firmware will order
// the keymaps.
enum layers {
    _FIRST,
    _COLEMAK,
    _GAMING,
    _SECOND,
    _THIRD,
    _FOURTH,
};

#ifdef OLED_ENABLE

#include "crab.c"

static void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return 1;
}

static void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
    case _FIRST:
        oled_write_ln_P(PSTR("Main"), false);
        break;
    case _SECOND:
        oled_write_ln_P(PSTR("Nav"), false);
        break;
    case _THIRD:
        oled_write_ln_P(PSTR("Sym"), false);
        break;
    case _FOURTH:
        oled_write_ln_P(PSTR("FnKeys"), false);
        break;
    case _GAMING:
        oled_write_ln_P(PSTR("Game"), false);
        break;
    case _COLEMAK:
        oled_write_ln_P(PSTR("Cole"), false);
        break;

    default:
        oled_write_ln_P(PSTR("Undef"), false);
        break;
    }
}

/* static const char *depad_stri(const char *depad_stri, char depad_char) { */
/*     while (*depad_stri == depad_char) */
/*         ++depad_stri; */
/*     return depad_stri; */
/* } */
// static void set_keylog(uint16_t keycode, keyrecord_t *record) {
//     // save the row and column (useful even if we can't find a keycode to
//     show) last_row = record->event.key.row; last_col = record->event.key.col;
//
//     keyname     = ' ';
//     last_keycode = keycode;
//     if (IS_QK_MOD_TAP(keycode)) {
//         if (record->tap.count) {
//             keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
//         } else {
//             keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) +
//             biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
//         }
//     } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
//         keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
//     } else if (IS_QK_MODS(keycode)) {
//         keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
//     } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
//         keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) +
//         biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
//     }
//     if (keycode > ARRAY_SIZE(code_to_name)) {
//         return;
//     }
//
//     // update keylog
//     keyname = pgm_read_byte(&code_to_name[keycode]);
// }
//
//
/* static void oled_render_keylog(void) { */
/*     oled_write_char('0' + last_row, false); */
/*     oled_write_P(PSTR("x"), false); */
/*     oled_write_char('0' + last_col, false); */
/*     oled_write_P(PSTR(", k"), false); */
/*     const char *last_keycode_str = get_u16_str(last_keycode, ' '); */
/*     oled_write(depad_stri(last_keycode_str, ' '), false); */
/*     oled_write_P(PSTR(":"), false); */
/*     oled_write_char(keyname, false); */
/* } */

//
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        /* oled_render_keylog(); */
    }

    if (!is_keyboard_master()) {
        oled_render_anim();
    }
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FIRST] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        KC_QUOT,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
        KC_SLSH, KC_LGUI,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, MO(3), KC_SPC, KC_ENT, MO(4), KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [_COLEMAK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y,
        KC_SEMICOLON, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O,
        KC_QUOT,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT,
        KC_SLSH, KC_LGUI,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, MO(3), KC_SPC, KC_ENT, MO(4), KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [_GAMING] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RALT, KC_0, KC_4, KC_5,
        KC_6, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LGUI, KC_PRINT_SCREEN, KC_LSFT, KC_LALT, KC_RALT, KC_DEL, KC_END,
        KC_1, KC_2, KC_3, XXXXXXX, KC_LGUI,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, _______, KC_SPC, KC_ENT, MO(3), KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [_SECOND] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RALT, KC_0, KC_4, KC_5,
        KC_6, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LGUI, KC_PRINT_SCREEN, KC_LSFT, KC_LALT, KC_RALT, KC_DEL, KC_END,
        KC_1, KC_2, KC_3, XXXXXXX, KC_LGUI,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, _______, KC_SPC, KC_ENT, MO(5), KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [_THIRD] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR,
        KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,
        KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS,
        KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, MO(5), KC_SPC, KC_ENT, _______, KC_RALT
        //`--------------------------'  `--------------------------'
        ),

    [_FOURTH] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.
        //,-----------------------------------------------------.
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_F10, KC_F11,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, QK_MAKE, XXXXXXX, KC_F12, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------|
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|
        //|--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, _______, KC_SPC, KC_ENT, _______, KC_RALT
        //`--------------------------'  `--------------------------'
        ),

};
