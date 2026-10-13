/* func_ov119_0229a400 @ 0x0229a400, 0xe bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a400 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
};

void func_ov119_0229a400(struct UnkStruct_0229a400 *p, unsigned short mask)
{
    unsigned short tmp;
    tmp = p->unk_98;
    tmp &= ~mask;
    p->unk_98 = tmp;
}
