/* func_0206c480 @ 0x0206c480, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206c480 {
    unsigned int pad_00[11];
    unsigned int unk_2C;
} UnkStruct_0206c480;

extern void func_0206d420(void);

// clang-format off
asm int func_0206c480(register UnkStruct_0206c480 *self)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x18ac
    add r2, r2, r1
    ldr r1, =0x114
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
