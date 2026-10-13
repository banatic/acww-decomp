/* func_020b0918 @ 0x020b0918, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

struct UnkStruct_020b0918 {
    char pad_00[2];
    unsigned short field_2 : 7;
    unsigned short : 9;
    unsigned char unk_04;
};

int func_020b0918(struct UnkStruct_020b0918 *p)
{
    int r4 = p->field_2 << 7;
    int r1;
    if (r4 == 0) {
        r4 = 0x1000;
    }
    r1 = 0x1000;
    if (p->unk_04 == 1) {
        r1 = FX_Div(0x3000, 0x4000);
    } else if (p->unk_04 == 2) {
        r1 = FX_Div(r1, 0x2000);
    }
    if (r1 > 0x1000) {
        r1 = 0x1000;
    }
    return FX_MulFunc(r4, r1);
}
