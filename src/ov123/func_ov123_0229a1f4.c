/* func_ov123_0229a1f4 @ 0x0229a1f4, 0x30 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a1f4 {
    unsigned char pad_00[0xa7];
    unsigned char unk_A7;
};

extern void func_ov123_0229a224(struct UnkStruct_0229a1f4 *p);

void func_ov123_0229a1f4(struct UnkStruct_0229a1f4 *p)
{
    if (p->unk_A7 != 0) {
        p->unk_A7--;
        if (p->unk_A7 == 0) {
            func_ov123_0229a224(p);
        }
    }
}
