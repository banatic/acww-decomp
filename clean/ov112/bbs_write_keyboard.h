/* The keys of overlay 95's keyboard (ov095/soft_keyboard.h) the bulletin board scene of
 * overlay 112 acts on. Its keys are numbered; a key has a code (SoftKeyboard_KeyCode) and can
 * be disabled (a bit of its word 0x20). */
#ifndef CLEAN_OV112_BBS_WRITE_KEYBOARD_H
#define CLEAN_OV112_BBS_WRITE_KEYBOARD_H

#include "types.h"

/* The keys the scene enables and disables, and those L and R show pressed. */
#define BBS_WRITE_KEY_NEWLINE 0
#define BBS_WRITE_KEY_6 6
#define BBS_WRITE_KEY_COPY 11
#define BBS_WRITE_KEY_PASTE 12
#define BBS_WRITE_KEY_L 0x109
#define BBS_WRITE_KEY_R 0x10a

/* The keyboard's layer (LAYER_SUB_BG3) and the code mode keys are read in. */
#define BBS_WRITE_KEYBOARD_LAYER 6
#define BBS_WRITE_CODE_MODE 9

#endif
