/* func_ov134_0229a1b4 @ 0x0229a1b4, 0x24 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200284c(int, int, int);

struct UnkStruct_0229a1b4 {
    int unk_00;
    unsigned char pad_04[0xa0];
    unsigned char unk_A4;
    unsigned char pad_A5[5];
    unsigned char unk_AA;
    unsigned char unk_AB;
};

int func_ov134_0229a1b4(struct UnkStruct_0229a1b4 *p)
{
    return func_0200284c(p->unk_A4, -p->unk_AA, -(p->unk_AB - p->unk_00));
}
