/* func_ov147_02299118 @ 0x02299118, 0x1c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200277c(int);
extern void func_0203de68(void);

// clang-format off
asm void func_ov147_02299118(int arg0)
{
    push {r4, lr}
    mov r4, r0
    mov r0, #5
    bl func_0200277c
    mov r0, #1
    bl func_0203de68
    mov r0, #5
    add r4, #0xaa
    strb r0, [r4]
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
