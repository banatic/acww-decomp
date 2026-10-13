/* func_ov003_02222318 @ 0x02222318, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02236c18[];
extern int data_ov003_02236c5c[];
extern void func_ov003_02222860(void *p);

struct UnkStruct_02222318 {
    char pad_00[0x3c];
    int unk_3C;
    int unk_40;
    int unk_44;
    char pad_48[0x4e - 0x48];
    unsigned short unk_4E;
};

void func_ov003_02222318(struct UnkStruct_02222318 *p)
{
    if (p->unk_4E >= 16) {
        p->unk_4E = 16;
        func_ov003_02222860(p);
    }
    p->unk_3C = data_ov003_02236c18[p->unk_4E];
    p->unk_44 = p->unk_3C;
    p->unk_40 = data_ov003_02236c5c[p->unk_4E];
}
