/* func_ov002_022080a0 @ 0x022080a0, 0x6 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[143];
    unsigned char unk_8F;
} UnkStruct_022080a0;
// clang-format off
asm unsigned char *func_ov002_022080a0(register UnkStruct_022080a0 *p, register unsigned char v)
{
    add r0, #0x8f
    strb r1, [r0]
    bx lr
}
// clang-format on
