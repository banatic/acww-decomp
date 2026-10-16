/* A d-pad key repeat of the menu scenes (vtable data_ov002_0220bb14): a key held fires after
 * `first_delay` frames, then again with a delay that shrinks by `speedup` down to
 * `min_delay`. Each frame KeyRepeat_Update gathers the keys that fired, KeyRepeat_Latch takes
 * them, and the tests read what it took.
 *
 * Its bytes hold d-pad bits as the buttons do (KeyRepeatKey). */
#ifndef CLEAN_OV002_KEY_REPEAT_H
#define CLEAN_OV002_KEY_REPEAT_H

#include "types.h"

enum KeyRepeatKey { KEY_REPEAT_RIGHT = 0x10, KEY_REPEAT_LEFT = 0x20, KEY_REPEAT_UP = 0x40, KEY_REPEAT_DOWN = 0x80 };

#define KEY_REPEAT_DPAD 0xf0

typedef struct KeyRepeat {
    const void *vtable;
    s16 first_delay; /* 0x04 */
    s16 min_delay;   /* 0x06 */
    s16 speedup;     /* 0x08 */
    s16 delay;       /* 0x0a */
    s16 countdown;   /* 0x0c */
    u8 held;         /* 0x0e: the d-pad keys held */
    u8 fired;        /* 0x0f: keys fired since the last KeyRepeat_Latch */
    u8 latched;      /* 0x10: the keys it took */
    u8 pad_11[3];
} KeyRepeat;

void KeyRepeat_Set(KeyRepeat *keys, unsigned short first_delay, unsigned short min_delay, unsigned short speedup);
int KeyRepeat_HasRight(int keys);
int KeyRepeat_HasLeft(int keys);
int KeyRepeat_HasDown(int keys);
int KeyRepeat_HasUp(int keys);
int KeyRepeat_Right(KeyRepeat *keys);
int KeyRepeat_Left(KeyRepeat *keys);
int KeyRepeat_Down(KeyRepeat *keys);
int KeyRepeat_Up(KeyRepeat *keys);
unsigned char KeyRepeat_Latch(KeyRepeat *keys);
void KeyRepeat_Update(KeyRepeat *keys);
KeyRepeat *KeyRepeat_Delete(KeyRepeat *keys);
void KeyRepeat_Destroy(KeyRepeat *keys);
void KeyRepeat_Construct(KeyRepeat *keys);

#endif
