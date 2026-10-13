/* func_ov134_022999ac @ 0x022999ac, 0x32 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a4d4(void *);

struct UnkStruct_022999ac {
    int unk_00;
    int unk_04;
    unsigned char pad_08[0x10];
    unsigned char sub;
    unsigned char pad_19[0x92];
    unsigned char unk_AB;
    unsigned char pad_AC[4];
    unsigned char unk_B0;
};

int func_ov134_022999ac(struct UnkStruct_022999ac *p)
{
    if (p->unk_B0 == 0) {
        return func_ov002_0220a4d4(&p->sub);
    } else {
        return p->unk_AB + ((p->unk_B0 - 1) << 4) - p->unk_00 + 8 - p->unk_04;
    }
}
