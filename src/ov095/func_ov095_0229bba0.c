/* func_ov095_0229bba0 @ 0x0229bba0, 0x20 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_022999c0(int a);

// clang-format off
asm int func_ov095_0229bba0(int a, unsigned short *b, int c, int d)
{
    push {lr}
    sub sp, #4
    cmp r3, #0
    bne append
    mov r0, #0
    b complete
append:
    sub r3, r3, #1
    lsl r3, r3, #1
    strh r2, [r1, r3]
    mov r1, r2
    bl func_ov095_022999c0
    mov r0, #1
complete:
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
