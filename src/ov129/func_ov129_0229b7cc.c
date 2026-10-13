/* func_ov129_0229b7cc @ 0x0229b7cc, 0xe bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b7cc {
    char pad_00[0xA4];
    unsigned short unk_A4;
};
void func_ov129_0229b7cc(struct UnkStruct_0229b7cc *p, unsigned short mask)
{
    p->unk_A4 = p->unk_A4 & ~mask;
}
