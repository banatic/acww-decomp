/* What the keyboard entry scene's files (keyboard_entry.h) read beyond the Clean functions
 * they call (overlay 95's keyboard, ov095/soft_keyboard.h, and overlay 124's entry field,
 * ov124/han_panel.h): main's buttons and touch, and the keys, codes and layers they use. */
#ifndef CLEAN_OV126_KEYBOARD_ENTRY_CALLS_H
#define CLEAN_OV126_KEYBOARD_ENTRY_CALLS_H

#include <stdint.h>

#include "autoload_2/input.h"
#include "keyboard_entry.h"
#include "types.h"

/* The buttons, and the pen: down, down or up since the frame before, and where. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* the touch's x */
extern u8 data_021f6c54; /* and its y */

#define KEYBOARD_ENTRY_PAD_A 0x0001
#define KEYBOARD_ENTRY_PAD_B 0x0002
#define KEYBOARD_ENTRY_PAD_START 0x0008
#define KEYBOARD_ENTRY_PAD_R 0x0100
#define KEYBOARD_ENTRY_PAD_L 0x0200

/* The sounds (SoundSys_PlaySe). */
#define KEYBOARD_ENTRY_SE_MOVE 0x0b   /* the text cursor moved by the d-pad */
#define KEYBOARD_ENTRY_SE_MARK 0x15   /* the marked range changed */
#define KEYBOARD_ENTRY_SE_OK 0x27     /* the panel's buttons, by KEYBOARD_ENTRY_FLAG_NEW_FRIEND and */
#define KEYBOARD_ENTRY_SE_CANCEL 0x28 /* KEYBOARD_ENTRY_FLAG_CANCELLED */
#define KEYBOARD_ENTRY_SE_OK_FRIEND 0x29
#define KEYBOARD_ENTRY_SE_CANCEL_FRIEND 0x2a
#define KEYBOARD_ENTRY_SE_BUZZ 0x34   /* nothing could be done */
#define KEYBOARD_ENTRY_SE_DELETE 0x35 /* a character deleted */

/* The keyboard's keys and codes the scene acts on (SoftKeyboard_KeyCode gives a key's code). */
#define KEYBOARD_ENTRY_KEY_0 0 /* always disabled here */
#define KEYBOARD_ENTRY_KEY_6 6 /* enabled with the character before the cursor */
#define KEYBOARD_ENTRY_KEY_COPY 11
#define KEYBOARD_ENTRY_KEY_PASTE 12
#define KEYBOARD_ENTRY_KEY_107 0x107 /* not pressed by A while the panel's OK button is dimmed */
#define KEYBOARD_ENTRY_KEY_L 0x109   /* the keys shown pressed by L and R */
#define KEYBOARD_ENTRY_KEY_R 0x10a
#define KEYBOARD_ENTRY_CODE_BACKSPACE 0x100
#define KEYBOARD_ENTRY_CODE_CONVERT_1 0x103 /* the character before the cursor converted */
#define KEYBOARD_ENTRY_CODE_CONVERT_2 0x104
#define KEYBOARD_ENTRY_CODE_CONVERT_3 0x105
#define KEYBOARD_ENTRY_CODE_OK 0x116
#define KEYBOARD_ENTRY_CODE_CANCEL 0x117
#define KEYBOARD_ENTRY_CODE_COPY 0x118
#define KEYBOARD_ENTRY_CODE_PASTE 0x119
#define KEYBOARD_ENTRY_KEY_MODE 9    /* the mode handed to SoftKeyboard_KeyCode */
#define KEYBOARD_ENTRY_LAYER 6       /* the sub screen's background 3, the keyboard's */
#define KEYBOARD_ENTRY_FIELD_LAYER 4 /* the sub screen's background 1 */

#define KEYBOARD_ENTRY_CURSOR_Y 0x28

static inline void *keyboard_entry_keyboard(KeyboardEntry *self)
{
    return self->keyboard;
}

static inline MenuScene *keyboard_entry_scene(KeyboardEntry *self)
{
    return &self->base;
}

/* The pointer's update through its class (vtable slot 3). */
static inline int keyboard_entry_update_pointer(KeyboardEntry *self)
{
    int (*const *vtable)(Glider *) = (int (*const *)(Glider *)) self->pointer.vtable;
    return vtable[3](&self->pointer);
}

#endif
