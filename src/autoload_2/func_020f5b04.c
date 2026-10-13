/* func_020f5b04 @ 0x020f5b04, 0x11c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int FX_Div(int a, int b);

struct UnkStruct_020f5b04 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
};

void func_020f5b04(struct UnkStruct_020f5b04 *p, int val)
{
    int x;
    int m;

    if (p->unk_00 == val) {
        return;
    }

    p->unk_00 = val;
    x = p->unk_00 - 0xB000;

    p->unk_04 = 0x7f000 - (int) (((long long) x * 0x3000 + 0x800) >> 12);
    p->unk_08 = 0x68000 - (int) (((long long) x * 0x4000 + 0x800) >> 12);
    m = FX_Div(0x2000, 0x3000);
    p->unk_0C = (int) (((long long) m * x + 0x800) >> 12) + 0x4000;
    m = FX_Div(0x4000, 0x3000);
    p->unk_10 = (int) (((long long) m * x + 0x800) >> 12) + 0x11000;
    p->unk_14 = FX_Div(p->unk_04 - p->unk_08, p->unk_0C - p->unk_00);
    p->unk_18 = FX_Div(p->unk_08, p->unk_00 - p->unk_10);
}