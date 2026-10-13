/* func_ov103_0229d724 @ 0x0229d724, 0x98 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct Param {
    char pad_00[0x2b98];
    int unk_2B98;
    int unk_2B9C;
    char pad_2BA0[0x2da3 - 0x2b9c - 4];
    unsigned char unk_2DA3;
} Param;

extern unsigned char data_021fbdd8;
extern int func_ov103_0229cd98(Param *, int, int, int);
extern int func_ov103_0229cc3c(Param *, int);
extern int func_ov103_0229cd4c(Param *, int);
extern void func_ov103_0229ce18(Param *, unsigned char, int);
extern void func_ov103_0229cfa0(Param *);
extern void func_ov103_0229cb60(Param *, int);
extern void func_ov103_0229c9c8(Param *);
extern void func_ov103_0229cb90(Param *);

void func_ov103_0229d724(Param *p)
{
    int r;
    func_ov103_0229c9c8(p);
    func_ov103_0229cb90(p);
    r = func_ov103_0229cd98(p, p->unk_2B98 + 8, p->unk_2B9C + 8, 0);
    if (r != 0x15) {
        if (data_021fbdd8 == 0) {
            if (func_ov103_0229cc3c(p, r) != 0 || func_ov103_0229cd4c(p, r) == 0) {
                func_ov103_0229ce18(p, p->unk_2DA3, 4);
            } else {
                func_ov103_0229cfa0(p);
            }
        } else {
            func_ov103_0229cb60(p, r);
        }
    } else {
        if (data_021fbdd8 == 0) {
            func_ov103_0229ce18(p, p->unk_2DA3, 4);
        }
    }
}
