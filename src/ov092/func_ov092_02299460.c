/* func_ov092_02299460 @ 0x02299460, 0x1e bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

extern void func_020041ec(void);
extern void func_0206ef34(void);
extern void func_0206f54c(void);
extern void func_ov092_02298f58(void);

// clang-format off
asm int func_ov092_02299460(char *self)
{
    push {r4, lr}
    mov r4, r0
    bl func_0206f54c
    bl func_0206ef34
    mov r0, r4
    bl func_ov092_02298f58
    bl func_020041ec
    mov r0, #1
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
