/* func_ov096_0229e0f8 @ 0x0229e0f8, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c878(unsigned short *);
extern int func_ov096_0229e158(void);
extern void func_ov096_0229e128(void *, int);

// clang-format off
asm void func_ov096_0229e0f8(void *a, unsigned short b)
{
    push {r4, r5, lr}
    sub sp, #4
    mov r5, r0
    add r0, sp, #0
    strh r1, [r0]
    add r0, sp, #0
    bl func_0204c878
    mov r4, r0
    mov r0, r5
    bl func_ov096_0229e158
    mov r0, r5
    bl func_ov096_0229e158
    mov r1, r0
    mov r0, r5
    sub r1, r1, r4
    bl func_ov096_0229e128
    add sp, #4
    pop {r4, r5}
    pop {r3}
    bx r3
}
// clang-format on
