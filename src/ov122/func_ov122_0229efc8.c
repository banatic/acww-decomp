/* func_ov122_0229efc8 @ 0x0229efc8, 0xe bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned short unk_A8;
} UnkStruct_0229efc8;

void func_ov122_0229efc8(UnkStruct_0229efc8 *p, unsigned short mask)
{
    p->unk_A8 &= ~mask;
}
