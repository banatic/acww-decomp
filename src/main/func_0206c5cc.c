/* func_0206c5cc @ 0x0206c5cc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

struct UnkStruct_0206c5cc {
    unsigned char pad_00[0x2c];
    unsigned int unk_2C;
};

struct UnkStruct_0206c5cc_2 {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
};

// clang-format off
asm void func_0206c5cc(register struct UnkStruct_0206c5cc *self)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r1, r2, r1
    add r1, #0x5c
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
