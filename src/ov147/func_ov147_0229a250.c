/* func_ov147_0229a250 @ 0x0229a250, 0x2e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_0229a594(void *object);
extern void func_ov147_0229a31c(void *object);
extern void func_ov147_0229a300(void);
extern void func_ov147_0229a374(void);
extern void func_ov147_0229a2f4(int *arg);

// clang-format off
asm int func_ov147_0229a250(int arg)
{
    push {r4, r5, lr}
    sub sp, #4
    mov r5, r0
    bl func_ov147_0229a594
    mov r4, r0
    mov r0, r5
    bl func_ov147_0229a31c
    cmp r4, #0
    beq complete
    mov r0, r5
    bl func_ov147_0229a300
    bl func_ov147_0229a374
    mov r0, r5
    bl func_ov147_0229a2f4
complete:
    add sp, #4
    pop {r4, r5}
    pop {r3}
    bx r3
}
// clang-format on
