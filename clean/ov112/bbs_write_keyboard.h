/* The keyboard of overlay 95 as the bulletin board scene of overlay 112 calls it (no Clean
 * version yet; the same functions overlay 122's letter writing calls, declared as
 * ov122/letter_write_scene.c does). Its keys are numbered; a key has a code
 * (func_ov095_0229c448) and can be disabled (a bit of its word 0x20). */
#ifndef CLEAN_OV112_BBS_WRITE_KEYBOARD_H
#define CLEAN_OV112_BBS_WRITE_KEYBOARD_H

#include "types.h"

extern void func_ov095_022999e8(void *keyboard); /* sound 23 */
extern void func_ov095_022999f4(void *keyboard); /* sound 22 */
/* The key its cursor is on, -1 when that key cannot be pressed now. */
extern int func_ov095_02299a00(void *keyboard);
/* The cursor moved by the d-pad keys: 1-3 when it leaves the keys toward the text (the
 * pointer's turn), 0 or 4 otherwise. */
extern int func_ov095_02299a54(void *keyboard, int keys);
extern void func_ov095_02299aec(void *keyboard); /* sets its key place by its mode */
extern void func_ov095_02299b30(int *keyboard, int x, int y);
extern int func_ov095_02299b38(void *keyboard); /* the key's y */
extern int func_ov095_02299b7c(void *keyboard); /* the key's x */
extern void func_ov095_0229ae84(void *keyboard, void *x, void *y);
extern int func_ov095_0229af58(int unused, int x, int y, int priority); /* the text cursor drawn */
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
/* The character of a text of `length` characters (at most `limit` pixels wide) whose middle is
 * past `x` pixels, into *index; gives the pixels before it. */
extern unsigned char func_ov095_0229bb34(int unused, const unsigned short *text, int length, int limit, unsigned char x,
                                         unsigned char *index);
extern int func_ov095_0229bb94(void *keyboard, int character); /* the conversions: 0 for none */
extern int func_ov095_0229bb98(void *keyboard, int character);
extern int func_ov095_0229bb9c(void *keyboard, int character);
/* The character before `position` replaced. */
extern int func_ov095_0229bba0(int keyboard, unsigned short *text, int character, int position);
/* Deletes the characters from `from` to `to` of a text of `length`, filling the end with 0;
 * gives the lower of the two. */
extern int func_ov095_0229bbc0(int unused, unsigned short *text, int from, int to, int length);
/* A character put into a text at *position, its lines broken as the view breaks them; with
 * `test_only` the text is left as it was. 1 when it fits. */
extern int func_ov095_0229bc00(void *keyboard, u16 *text, int character, u8 *position, int length, int max_chars, int lines,
                               int width, int test_only, int notify);
extern int func_ov095_0229bebc(void *keyboard, int code);            /* the code is a command (0x100-0x123) */
extern void func_ov095_0229bed8(void *keyboard, int character);      /* key 6 enabled */
extern void func_ov095_0229bee4(void *keyboard);                     /* keys 6, 3, 4 and 5 disabled */
extern int func_ov095_0229bf0c(void *keyboard);                      /* a held key's repeat is due */
extern void func_ov095_0229bf3c(void *keyboard);                     /* a held key's repeat started */
extern int func_ov095_0229bf48(void *keyboard);                      /* the pressed key shown: 1 while it shows */
extern void func_ov095_0229bf7c(void *keyboard, unsigned int layer); /* drawn */
extern void func_ov095_0229bfd8(void *keyboard, int layer);
extern int func_ov095_0229c000(void *keyboard, const char *path);
extern int func_ov095_0229c01c(void *keyboard, int layer); /* its characters loaded on `layer` */
extern void func_ov095_0229c05c(void *keyboard);
extern void func_ov095_0229c084(void *keyboard, int mode);
extern void func_ov095_0229c22c(void *keyboard, int state, unsigned int layer, int p3);
extern void func_ov095_0229c420(void *keyboard, int layer);
extern int func_ov095_0229c448(void *keyboard, int key, unsigned int mode); /* the key's code */
extern int func_ov095_0229c548(void *keyboard);                             /* the key held down */
extern int func_ov095_0229c54c(void *keyboard, int x, u8 y);                /* the key at (x, y), or -1 */
extern void func_ov095_0229c8e4(int keyboard, int key);                     /* the key shown pressed */
extern void func_ov095_0229cce0(void *keyboard);                            /* releases its pressed keys */
extern void func_ov095_0229cd30(int keyboard);                              /* resets its keys */
extern int func_ov095_0229cda4(void *keyboard, int key);                    /* the key (-1: the cursor's) is 0x104-0x108 */
extern void func_ov095_0229ce84(void *keyboard, int key);                   /* the key enabled */
extern void func_ov095_0229cef4(void *keyboard, int key);                   /* the key disabled */
extern int func_ov095_0229cf64(void *keyboard, int key);                    /* the key is disabled */

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
