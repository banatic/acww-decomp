/* func_0206f9d8 @ 0x0206f9d8, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_020984e8(void *);
extern void *func_02099734(u32);
extern void *func_02098f48(void *, int);
extern int func_02098e8c(void *, int);

u16 func_0206f9d8(int (*cb)(u16 *, int))
{
    u32 h;
    u16 *t;
    int i;
    u16 mask;

    h = func_020984e8((void *) cb);
    t = (u16 *) func_02098f48(func_02099734(h), 0);
    mask = 0;

    for (i = 0; i < 15; i++) {
        if (cb(t + i, func_02098e8c(func_02099734(h), i)) != 0) {
            mask |= (1 << i);
        }
    }

    return mask;
}
