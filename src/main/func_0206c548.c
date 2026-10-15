/* func_0206c548 @ 0x0206c548, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct St {
    char pad_00[0x2c];
    unsigned int unk_2C;
};

extern void func_0206d420(void);

// clang-format off
asm void func_0206c548(register struct St *p)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x228
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
