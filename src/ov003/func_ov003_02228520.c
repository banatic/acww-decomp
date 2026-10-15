/* func_ov003_02228520 @ 0x02228520, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_022284a8(void *self);
void func_ov003_0222847c(void);
void func_ov003_02228460(void);

// clang-format off
asm int func_ov003_02228520(void *self)
{
    push {r4, lr}
    mov r4, r0
    bl func_ov003_022284a8
    mov r0, r4
    bl func_ov003_0222847c
    mov r0, r4
    bl func_ov003_02228460
    mov r0, #1
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
