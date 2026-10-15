/* func_ov068_02274490 @ 0x02274490, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02274490 {
    char pad_00[0x730];
    int value;
};

struct Main {
    char pad_00[0xb4];
    struct UnkStruct_02274490 *sub;
};

extern void func_ov068_0227440c(struct Main *param);

// clang-format off
asm void func_ov068_02274490(struct Main *param, int arg2)
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
    bl func_ov068_0227440c
complete:
    add sp, #4
    pop {r3}
    bx r3
}
// clang-format on
