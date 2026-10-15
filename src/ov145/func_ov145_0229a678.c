/* func_ov145_0229a678 @ 0x0229a678, 0x50 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af94(void);
extern int func_02002c6c(char *a, int b, int c, int d, int e, int f);
extern int func_02002d14(char *a, int b, int c, int d, int e, int f);
extern int data_021fbe94;
extern char data_ov145_0229aee0[];
extern char data_ov145_0229aef8[];

// clang-format off
asm void func_ov145_0229a678(char *param)
{
    push {r4, lr}
    sub sp, #8
    ldr r1, =0x174
    add r0, r0, r1
    bl func_ov002_0220af94
    ldr r0, =data_021fbe94
    ldr r4, [r0]
    mov r3, #0xc0
    str r3, [sp]
    ldr r0, =0x13f
    str r0, [sp, #4]
    ldr r0, =data_ov145_0229aee0
    mov r1, r4
    mov r2, #8
    bl func_02002c6c
    mov r3, #4
    str r3, [sp]
    mov r0, #9
    str r0, [sp, #4]
    ldr r0, =data_ov145_0229aef8
    mov r1, r4
    mov r2, #8
    bl func_02002d14
    add sp, #8
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
