/// Author: @poliorcetics
///
/// This layout is heavily based on <https://github.com/manna-harbour/miryoku>.
///
/// I did not use it directly because I wanted to learn about QMK and interacting with it that way is
/// a good way to do so instead of relying entirely on someone else's work.
///
/// Miryoku and its authors and contributors deserve praise though, it helped me a lot in figuring out
/// stuff by looking at how they did it.
///
/// All keys can be found at <https://docs.qmk.fm/#/keycodes>.

#include "keycodes.h"
#include QMK_KEYBOARD_H

// <https://docs.qmk.fm/#/keycodes?id=mod-tap-keys>

/// When held: Left Shift
#define LS(kc) LSFT_T(KC_ ## kc)
/// When held: Left Control
#define LC(kc) LCTL_T(KC_ ## kc)
/// When held: Left Windows/Command
#define LG(kc) LGUI_T(KC_ ## kc)

/// When held: Right Shift
#define RS(kc) RSFT_T(KC_ ## kc)
/// When held: Right Control
#define RC(kc) RCTL_T(KC_ ## kc)
/// When held: Right Windows/Command
#define RG(kc) RGUI_T(KC_ ## kc)

/// The ALT keys are a little different: the right and left one are not equivalent and they both need
/// to be accessible and allow all possible key combinations on all layers.
/// To do that, I copied the Miryoku way: Left Alt/Option is the main one and below it is AltGr.
/// To mark this demarcation in layer definition, I used less shortened variants and no L/R marker

/// When held: Left Alt/Option
#define ALT(kc) LALT_T(KC_ ## kc)
/// When held: Right Alt/Option, aka AltGr
#define AGR(kc) ALGR_T(KC_ ## kc)

/// Ignored key (no-op)
#define __ KC_NO

/// Layer-tap switch
/// <https://docs.qmk.fm/#/keycodes?id=layer-switching>
#define L(num, kc) LT(num, KC_ ## kc)

/// General changes from the base Miryoku layout:
///
/// - The modifier order is Shift/Control/Alt/Gui (out->in) because that's the order on macOS
///   keyboards and I want the familiarity to avoid being confused each time I have to type on the
///   integrated keyboard.
///
/// - The right thumb cluster is different to better suit my needs, though I'm still unsure about
///   using `caps word (CW_TOGG)` on the base layer.
///
/// - Layers which have been entirely removed:
///   - Mouse layer, which I don't think is worth it compared to a good trackpad, especially on macOS
///   - Button layer, for the same reason: what would I use it for ?
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /// Base layer
    ///
    /// Replaced delete by the caps word toggle on outermost right thumb key.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#base>
    [0] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,                   KC_J,         KC_L,         KC_U,         KC_Y,      KC_QUOT,
       LS(A),        LC(R),       ALT(S),        LG(T),         KC_G,                   KC_M,        RG(N),       ALT(E),        RC(I),        RS(O),
        KC_Z,         KC_X,       AGR(C),         KC_D,         KC_V,                   KC_K,         KC_H,    AGR(COMM),       KC_DOT,      KC_SLSH,
                               L(1, ESC),    L(2, SPC),       KC_TAB,             L(3, BSPC),    L(4, ENT),    L(5, ESC)
    ),

    /// RIGHT HAND LAYERS
    /// =================
    ///
    /// Layers where the actual non-modifier keys are on the right hand (and so the tap-hold is on the left hand).
    ///
    /// Layers from left to right (on thumb keys):
    /// - Media layer
    /// - Navigation layer

    /// Media layer
    ///
    /// On this layer, the top row has been removed, the keys in question are only useful on RGB boards.
    /// In the same vein, the bottom row with Bluetooth controls has been cleared and replaced with Brightness Down/Up (for the screen).
    ///
    /// NOTE: `MSTP` is only working on Windows and Linux.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#media>
    [1] = LAYOUT_split_3x5_3(
          __,           __,           __,           __,           __,                     __,           __,           __,           __,           __,
     KC_LSFT,      KC_LCTL,      KC_LALT,      KC_LGUI,           __,                     __,      KC_MPRV,      KC_VOLD,      KC_VOLU,      KC_MNXT,
          __,           __,      KC_ALGR,           __,           __,                     __,           __,      KC_BRID,      KC_BRIU,           __,
                                      __,           __,           __,                KC_MSTP,      KC_MPLY,      KC_MUTE
    ),
    /// Navigation layer
    ///
    /// On this layer, the top row has been removed, the keys in question are only available on Linux
    /// and not something I use even there.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#nav>
    [2] = LAYOUT_split_3x5_3(
          __,           __,           __,           __,           __,                     __,           __,           __,           __,           __,
     KC_LSFT,      KC_LCTL,      KC_LALT,      KC_LGUI,           __,                KC_CAPS,      KC_LEFT,      KC_DOWN,        KC_UP,     KC_RIGHT,
          __,           __,      KC_ALGR,           __,           __,                     __,      KC_HOME,      KC_PGDN,      KC_PGUP,       KC_END,
                                      __,           __,           __,                KC_BSPC,       KC_ENT,      CW_TOGG
    ),

    /// LEFT HAND LAYERS
    /// ================
    ///
    /// Layers where the actual non-modifier keys are on the left hand (and so the tap-hold is on the right hand).
    ///
    /// Layers from left to right (on thumb keys):
    /// - Symbol layer
    /// - Number layer
    /// - Function layer

    /// Symbol layer
    ///
    /// Nothing changed here, except for the modifiers order.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#sym>
    [3] = LAYOUT_split_3x5_3(
     KC_LCBR,      KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RCBR,                     __,           __,           __,           __,           __,
     KC_COLN,       KC_DLR,      KC_PERC,      KC_CIRC,      KC_PLUS,                     __,      KC_RGUI,      KC_LALT,      KC_RCTL,      KC_RSFT,
     KC_TILD,      KC_EXLM,        KC_AT,      KC_HASH,      KC_PIPE,                     __,           __,      KC_ALGR,           __,           __,
                                 KC_LPRN,      KC_RPRN,      KC_UNDS,                     __,           __,           __
    ),
    /// Number layer
    ///
    /// Nothing changed here, except for the modifiers order.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#num>
    [4] = LAYOUT_split_3x5_3(
     KC_LBRC,         KC_7,         KC_8,         KC_9,      KC_RBRC,                     __,           __,           __,           __,           __,
     KC_SCLN,         KC_4,         KC_5,         KC_6,       KC_EQL,                     __,      KC_RGUI,      KC_LALT,      KC_RCTL,      KC_RSFT,
      KC_GRV,         KC_1,         KC_2,         KC_3,      KC_BSLS,                     __,           __,      KC_ALGR,           __,           __,
                                  KC_DOT,         KC_0,      KC_MINS,                     __,           __,           __
    ),
    /// Function layer
    ///
    /// Removed the Scroll Lock and Pause/Break key in inner column, I don't care about them at all.
    /// Removed the App key on outer thumb key, kept the dot.
    ///
    /// <https://github.com/manna-harbour/miryoku/tree/9dc98b5d7fb2b88d375e7ce5ffbe1bfd5e2f5942/docs/reference#fun>
    [5] = LAYOUT_split_3x5_3(
      KC_F12,        KC_F7,        KC_F8,        KC_F9,      KC_PSCR,                     __,           __,           __,           __,           __,
      KC_F11,        KC_F4,        KC_F5,        KC_F6,           __,                     __,      KC_RGUI,      KC_LALT,      KC_RCTL,      KC_RSFT,
      KC_F10,        KC_F1,        KC_F2,        KC_F3,           __,                     __,           __,      KC_ALGR,           __,           __,
                                  KC_DOT,       KC_SPC,       KC_TAB,                     __,           __,           __
    ),
    // TODO(poliorcetics):
    // - Am still unsure about activation layer for features like going to the bootloader or locking the computer
    // - Am still unsure about an accent layer for French
};

#undef LS
#undef LC
#undef LG

#undef RS
#undef RC
#undef RG

#undef ALT
#undef AGR

#undef __

#undef L
