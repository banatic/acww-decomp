/* func_0206c580 @ 0x0206c580, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

struct Func0206c580_Unk {
    char pad_00[0x2c];
    char *ptr;
};

// clang-format off
asm void func_0206c580(register struct Func0206c580_Unk *self)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x170
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
