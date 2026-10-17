/* What the keyboard entry scene's files (keyboard_entry.h) call and read beyond the Clean
 * functions they name: overlay 95's keyboard and overlay 124's entry field (neither has Clean
 * versions yet), and main's buttons and touch. */
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

/* The keyboard's keys and codes the scene acts on (func_ov095_0229c448 gives a key's code). */
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
#define KEYBOARD_ENTRY_KEY_MODE 9    /* the mode handed to func_ov095_0229c448 */
#define KEYBOARD_ENTRY_LAYER 6       /* the sub screen's background 3, the keyboard's */
#define KEYBOARD_ENTRY_FIELD_LAYER 4 /* the sub screen's background 1 */

#define KEYBOARD_ENTRY_CURSOR_Y 0x28

/* The keyboard of overlay 95 (as ov122/letter_write_scene.c knows it). */
extern void func_ov095_022999e8(void *keyboard); /* sound 23 */
extern void func_ov095_022999f4(void *keyboard); /* sound 22 */
extern int func_ov095_02299a00(void *keyboard);  /* the key its cursor is on, -1 when it cannot be pressed */
/* The cursor moved by the d-pad keys: 1-3 when it leaves the keys toward the text, 4 too. */
extern int func_ov095_02299a54(void *keyboard, void *keys);
extern void func_ov095_02299aec(void *keyboard);      /* sets its key place by its mode */
extern int func_ov095_02299b38(void *keyboard);       /* the key's y */
extern int func_ov095_02299b7c(void *keyboard);       /* the key's x */
extern void func_ov095_0229a134(int keyboard, int x); /* its cursor put on the key below x */
extern void func_ov095_0229ae84(void *keyboard, void *x, void *y);
extern int func_ov095_0229af58(int unused, int x, int y, int priority); /* the text cursor's cell drawn */
extern int func_ov095_0229aff0(void *keyboard);                         /* a mode tab under the pen: the mode changed, 1 */
extern void func_ov095_0229b1c8(void *keyboard, int x, int y, int priority);
extern int func_ov095_0229b324(void *keyboard); /* its screen's files loaded */
extern void func_ov095_0229b388(int keyboard);  /* its flag 2 cleared */
extern void func_ov095_0229b394(int keyboard);  /* its flag 2 set */
/* A character being composed taken back (0 when there was none to take back). */
extern int func_ov095_0229b3a0(void *keyboard, u16 *text, int position);
extern void func_ov095_0229b3ec(void *keyboard); /* the composition dropped */
/* A code of the keyboard's own (the modes, the composition): what it did, 0 for none. */
extern int func_ov095_0229ba44(void *keyboard, int code, int layer);
/* The character of a text whose middle is past `x` pixels, into *index; gives the pixels before
 * it. */
extern unsigned char func_ov095_0229bb34(int unused, const unsigned short *text, int length, int width, unsigned char x,
                                         unsigned char *index);
extern int func_ov095_0229bb94(void *keyboard, int character); /* the conversions: 0 for none */
extern int func_ov095_0229bb98(void *keyboard, int character);
extern int func_ov095_0229bb9c(void *keyboard, int character);
/* The character before `position` replaced. */
extern int func_ov095_0229bba0(int keyboard, unsigned short *text, int character, int position);
/* Deletes the characters from `from` to `to`; gives the lower of the two. */
extern int func_ov095_0229bbc0(int unused, unsigned short *text, int from, int to, int length);
/* A character put into a one-line text at *position, at most `width` pixels wide. 1 when it fits. */
extern int func_ov095_0229bcec(int keyboard, int text, int character, int position, int length, int width, int p6, int notify);
extern int func_ov095_0229bebc(int keyboard, int code);              /* the code is a command (0x100-0x123) */
extern void func_ov095_0229bed8(void *keyboard, int character);      /* key 6 enabled */
extern void func_ov095_0229bee4(void *keyboard);                     /* keys 6, 3, 4 and 5 disabled */
extern int func_ov095_0229bf0c(void *keyboard);                      /* a held key's repeat is due */
extern void func_ov095_0229bf3c(void *keyboard);                     /* a held key's repeat started */
extern int func_ov095_0229bf48(void *keyboard);                      /* the pressed key shown: 1 while it shows */
extern void func_ov095_0229bf7c(void *keyboard, unsigned int layer); /* drawn */
extern void func_ov095_0229bfd8(void *keyboard, int layer);
extern int func_ov095_0229c000(int keyboard, int path);
extern int func_ov095_0229c01c(int keyboard, int layer);
extern void func_ov095_0229c05c(void *keyboard);
extern void func_ov095_0229c084(void *keyboard, int mode);
extern void func_ov095_0229c22c(void *keyboard, int state, unsigned int layer, int p3);
extern void func_ov095_0229c420(void *keyboard, int layer);                 /* set up in the mode main keeps */
extern int func_ov095_0229c448(void *keyboard, int key, unsigned int mode); /* the key's code */
extern int func_ov095_0229c548(void *keyboard);                             /* the key held down */
extern int func_ov095_0229c54c(void *keyboard, int x, u8 y);                /* the key at (x, y), or -1 */
extern void func_ov095_0229c8e4(int keyboard, int key);                     /* the key shown pressed */
extern void func_ov095_0229cce0(void *keyboard);                            /* releases its pressed keys */
extern void func_ov095_0229cd30(int keyboard);                              /* resets its keys */
extern void func_ov095_0229ce84(void *keyboard, int key);                   /* the key enabled */
extern void func_ov095_0229cef4(void *keyboard, int key);                   /* the key disabled */
extern int func_ov095_0229cf64(void *keyboard, int key);                    /* the key is disabled */

/* Overlay 124's entry field: a label (main/text_label.h) and a panel sprite (ov002/panel_sprite.h)
 * at 0x6c. Its kind (KeyboardEntryFieldKind) follows GroupParams' mode. */
extern void func_ov124_0229eea0(char *field);                   /* the label's box closed, the sprite's text too */
extern void func_ov124_0229eeb8(void *field, void *x, void *y); /* drawn */
extern void func_ov124_0229ef4c(void *field, int layer);
extern int func_ov124_0229f27c(int field);                                      /* its kind */
extern void func_ov124_0229f2c8(int field, int a, int b, int first, int count); /* TextLabel_SetBoxParams */
extern void func_ov124_0229f2dc(void *field, void *text, void *length);         /* TextLabel_SetFromWide */
extern void func_ov124_0229f2e4(int field);                                     /* shown (TextLabel_ShowAt) */
extern void func_ov124_0229f320(int field);                                     /* its box opened */
extern int func_ov124_0229f378(int field, int layer);
extern void *func_ov124_0229f43c(void *field); /* the destructor */
extern void *func_ov124_0229f460(void *field); /* the constructor */

static inline void *keyboard_entry_keyboard(KeyboardEntry *self)
{
    return self->keyboard;
}

static inline int keyboard_entry_keyboard_arg(KeyboardEntry *self)
{
    return (int) (uintptr_t) self->keyboard;
}

static inline int keyboard_entry_field_arg(KeyboardEntry *self)
{
    return (int) (uintptr_t) self->field;
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
