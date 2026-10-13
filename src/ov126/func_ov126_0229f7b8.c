/* func_ov126_0229f7b8 @ 0x0229f7b8, 0xe bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f7b8 {
    char pad_00[0xa4];
    unsigned short unk_A4;
};

void func_ov126_0229f7b8(struct UnkStruct_0229f7b8 *p, unsigned short v)
{
    p->unk_A4 |= v;
}
