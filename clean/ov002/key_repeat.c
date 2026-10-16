/* The d-pad key repeat of the menu scenes (key_repeat.h). */
#include "key_repeat.h"

#include <stddef.h>

#include "autoload_2/input.h"
#include "clean.h"

static_assert(offsetof(KeyRepeat, held) == 0x0e && offsetof(KeyRepeat, latched) == 0x10, "key repeat fields");
static_assert(sizeof(KeyRepeat) == 0x14, "key repeat size");

extern const u8 data_ov002_0220bb14[]; /* the key repeat's vtable */
extern PadState data_021fbe40;
extern void func_020edb3c(void *block); /* operator delete */

/* func_ov002_02208880: sets the delays and forgets the keys. */
void KeyRepeat_Set(KeyRepeat *keys, unsigned short first_delay, unsigned short min_delay, unsigned short speedup)
{
    keys->held = 0;
    keys->fired = 0;
    keys->latched = 0;
    keys->delay = 0;
    keys->countdown = 0;
    keys->first_delay = (s16) first_delay;
    keys->min_delay = (s16) min_delay;
    keys->speedup = (s16) speedup;
}
CLEAN_AS(func_ov002_02208880, KeyRepeat_Set)

/* func_ov002_0220889c: whether the keys `keys` (as KeyRepeat_Latch returns them) hold
 * right. */
int KeyRepeat_HasRight(int keys)
{
    return (keys & KEY_REPEAT_RIGHT) != 0;
}
CLEAN_AS(func_ov002_0220889c, KeyRepeat_HasRight)

/* func_ov002_022088ac */
int KeyRepeat_HasLeft(int keys)
{
    return (keys & KEY_REPEAT_LEFT) != 0;
}
CLEAN_AS(func_ov002_022088ac, KeyRepeat_HasLeft)

/* func_ov002_022088bc */
int KeyRepeat_HasDown(int keys)
{
    return (keys & KEY_REPEAT_DOWN) != 0;
}
CLEAN_AS(func_ov002_022088bc, KeyRepeat_HasDown)

/* func_ov002_022088cc */
int KeyRepeat_HasUp(int keys)
{
    return (keys & KEY_REPEAT_UP) != 0;
}
CLEAN_AS(func_ov002_022088cc, KeyRepeat_HasUp)

/* func_ov002_022088dc: whether the latched keys hold right. */
int KeyRepeat_Right(KeyRepeat *keys)
{
    return (keys->latched & KEY_REPEAT_RIGHT) != 0;
}
CLEAN_AS(func_ov002_022088dc, KeyRepeat_Right)

/* func_ov002_022088f0 */
int KeyRepeat_Left(KeyRepeat *keys)
{
    return (keys->latched & KEY_REPEAT_LEFT) != 0;
}
CLEAN_AS(func_ov002_022088f0, KeyRepeat_Left)

/* func_ov002_02208904 */
int KeyRepeat_Down(KeyRepeat *keys)
{
    return (keys->latched & KEY_REPEAT_DOWN) != 0;
}
CLEAN_AS(func_ov002_02208904, KeyRepeat_Down)

/* func_ov002_02208918 */
int KeyRepeat_Up(KeyRepeat *keys)
{
    return (keys->latched & KEY_REPEAT_UP) != 0;
}
CLEAN_AS(func_ov002_02208918, KeyRepeat_Up)

/* func_ov002_0220892c: takes the keys fired since the last call; returns them. */
unsigned char KeyRepeat_Latch(KeyRepeat *keys)
{
    keys->latched = keys->fired;
    keys->fired = 0;
    return keys->latched;
}
CLEAN_AS(func_ov002_0220892c, KeyRepeat_Latch)

/* func_ov002_02208938: a frame. Keys pressed this frame fire at once. While the same d-pad keys
 * stay held, they fire again each time the countdown runs out, the delay shrinking by
 * `speedup` each time down to `min_delay`; any change of the held keys (or none held) starts
 * over at `first_delay`. */
void KeyRepeat_Update(KeyRepeat *keys)
{
    u8 was_held = keys->held;
    u8 pressed = (u8) (data_021fbe40.pressed & KEY_REPEAT_DPAD);

    keys->held = (u8) (data_021fbe40.held & KEY_REPEAT_DPAD);
    keys->fired |= pressed;

    if (keys->held == 0 || was_held != keys->held) {
        keys->fired = pressed;
        keys->delay = keys->first_delay;
        keys->countdown = keys->first_delay;
    } else if (keys->countdown > 0) {
        keys->countdown--;
    } else {
        keys->fired |= keys->held;
        keys->delay = (s16) (keys->delay - keys->speedup);
        if (keys->delay < keys->min_delay) {
            keys->delay = keys->min_delay;
        }
        keys->countdown = keys->delay;
    }
}
CLEAN_AS(func_ov002_02208938, KeyRepeat_Update)

/* func_ov002_022089bc: the deleting destructor. */
KeyRepeat *KeyRepeat_Delete(KeyRepeat *keys)
{
    keys->vtable = data_ov002_0220bb14;
    func_020edb3c(keys);
    return keys;
}
CLEAN_AS(func_ov002_022089bc, KeyRepeat_Delete)

/* func_ov002_022089d4 */
void KeyRepeat_Destroy(KeyRepeat *keys)
{
    keys->vtable = data_ov002_0220bb14;
}
CLEAN_AS(func_ov002_022089d4, KeyRepeat_Destroy)

/* func_ov002_022089e0 */
void KeyRepeat_Construct(KeyRepeat *keys)
{
    keys->vtable = data_ov002_0220bb14;
}
CLEAN_AS(func_ov002_022089e0, KeyRepeat_Construct)
