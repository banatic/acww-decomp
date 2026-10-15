/* func_0206c4d8 @ 0x0206c4d8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void);

typedef struct {
    unsigned char data[0x14b8];
} BigStruct;

typedef struct {
    unsigned char pad_00[0x2c];
    BigStruct *big;
} UnkStruct_0206c4d8;

// clang-format off
asm void func_0206c4d8(register UnkStruct_0206c4d8 *obj)
{
    ldr r2, [r0, #0x2c]
    ldr r1, =0x14b8
    add r2, r2, r1
    ldr r1, =0x398
    add r1, r2, r1
    ldr r3, =func_0206d420
    bx r3
}
// clang-format on
