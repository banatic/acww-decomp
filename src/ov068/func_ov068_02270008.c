/* func_ov068_02270008 @ 0x02270008, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int a, int b);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02270008;

void func_ov068_02270008(int mode, UnkStruct_02270008 *p)
{
    if (mode == 1 || mode == 4) {
        p->unk_00 += FX_Div(0xfffff000, 0x10000);
        p->unk_04 = FX_Div(0x10000, 0x10000);
        p->unk_08 += FX_Div(0xffffc000, 0x10000);
    } else {
        p->unk_04 = FX_Div(0x9000, 0x10000);
        p->unk_08 += FX_Div(0x3000, 0x10000);
    }
}
