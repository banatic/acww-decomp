/* func_ov002_02208098 @ 0x02208098, 0x6 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[141];
    unsigned char unk_8D;
} UnkStruct_02208098;
// clang-format off
asm unsigned char *func_ov002_02208098(register UnkStruct_02208098 *p, register unsigned char v)
{
    add r0, #0x8d
    strb r1, [r0]
    bx lr
}
// clang-format on
