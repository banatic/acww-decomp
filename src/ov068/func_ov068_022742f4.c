/* func_ov068_022742f4 @ 0x022742f4, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02274238(void *a);

struct inner_022743ec {
    char pad_00[0x730];
    int value;
};

struct outer_022743ec {
    char pad_00[0xb4];
    struct inner_022743ec *inner;
};

// clang-format off
asm void func_ov068_022742f4(struct outer_022743ec *a, void *b)
{
    push {lr}
    sub sp, #4
    mov r2, r0
    add r2, #0xb4
    ldr r3, [r2]
    ldr r2, =0x730
    ldr r2, [r3, r2]
    cmp r2, #7
    bne complete
    bl func_ov068_02274238
complete:
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
