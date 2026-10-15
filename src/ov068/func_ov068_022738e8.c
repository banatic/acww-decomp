/* func_ov068_022738e8 @ 0x022738e8, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0227302c(void);

typedef struct {
    void *unk_00;
    void *unk_04;
} Ov68Self;

// clang-format off
asm void func_ov068_022738e8(Ov68Self *self)
{
    push {lr}
    sub sp, #4
    mov r2, r0
    ldr r0, [r2, #4]
    ldr r0, [r0, #0x2c]
    cmp r0, #0
    beq unchanged
    ldr r1, [r2]
    ldrb r1, [r1, #1]
    bl func_ov068_0227302c
unchanged:
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
