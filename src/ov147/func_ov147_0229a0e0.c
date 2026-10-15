/* func_ov147_0229a0e0 @ 0x0229a0e0, 0x2e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_0229a01c(void *);
extern void func_ov147_0229a6a8(void);
extern void func_020b9ccc(void *);
extern void func_0203e328(void);
extern void func_020a13e8(void);

// clang-format off
asm int func_ov147_0229a0e0(void *self)
{
    push {r4, lr}
    mov r4, r0
    bl func_ov147_0229a01c
    mov r0, r4
    add r0, #0xb0
    bl func_ov147_0229a6a8
    mov r0, r4
    add r0, #0xd0
    bl func_020b9ccc
    bl func_0203e328
    ldr r0, [r4, #0x50]
    cmp r0, #7
    bne complete
    bl func_020a13e8
complete:
    mov r0, #1
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
