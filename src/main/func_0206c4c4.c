/* func_0206c4c4 @ 0x0206c4c4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_0206c4c4;

// clang-format off
asm int func_0206c4c4(register UnkStruct_0206c4c4 *s)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x18ac
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
