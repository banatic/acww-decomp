/* func_ov111_0229efc8 @ 0x0229efc8, 0xe bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229efc8 {
    unsigned char pad_00[0xa4];
    unsigned short unk_A4;
};

void func_ov111_0229efc8(struct UnkStruct_0229efc8 *p, unsigned short v)
{
    p->unk_A4 |= v;
}
