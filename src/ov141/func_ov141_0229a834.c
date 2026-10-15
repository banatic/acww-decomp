/* func_ov141_0229a834 @ 0x0229a834, 0x1c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_02299964(void);
extern void func_ov002_0220af94(void);

// clang-format off
asm void func_ov141_0229a834(void *self)
{
    push {r4, lr}
    mov r4, r0
    add r0, #0x94
    bl func_ov139_02299964
    ldr r0, =0xa9c
    add r0, r4, r0
    bl func_ov002_0220af94
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
