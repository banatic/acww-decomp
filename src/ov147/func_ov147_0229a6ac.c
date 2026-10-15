/* func_ov147_0229a6ac @ 0x0229a6ac, 0x20 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

struct Struct_ov147_0229a6ac {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int pad_10;
    int pad_14;
    int unk_18;
};

extern void func_ov147_0229a608(struct Struct_ov147_0229a6ac *p);
extern void func_ov147_0229a2f4(struct Struct_ov147_0229a6ac *p);

void func_ov147_0229a6ac(struct Struct_ov147_0229a6ac *p)
{
    p->unk_04 = 0;
    p->unk_08 = 2;
    p->unk_18 = 0;
    p->unk_0C = 2;
    func_ov147_0229a608(p);
    func_ov147_0229a2f4(p);
}
