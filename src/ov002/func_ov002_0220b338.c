/* func_ov002_0220b338 @ 0x0220b338, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b29c(char *self, int value);
extern void func_ov002_0220b358(void *, unsigned char parameter1);

// clang-format off
asm int func_ov002_0220b338(register char *self, register unsigned char value)
{
    push {r4, lr}
    add r4, r0, #0
    bl func_ov002_0220b358
    mov r1, #0
    add r0, r4, #0
    add r0, #0x75
    strb r1, [r0]
    add r0, r4, #0
    mov r1, #1
    bl func_ov002_0220b29c
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
