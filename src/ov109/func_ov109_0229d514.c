/* func_ov109_0229d514 @ 0x0229d514, 0x7c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);

struct UnkStruct_0229d514 {
    unsigned char pad_00[0x29b4];
    unsigned int unk_29B4;
    unsigned char pad_29B8[0x29cf - 0x29b8];
    unsigned char unk_29CF;
    unsigned char pad_29D0[0x29d1 - 0x29d0];
    unsigned char unk_29D1;
    unsigned char pad_29D2[0x29d3 - 0x29d2];
    unsigned char unk_29D3;
    unsigned char pad_29D4[0x29d9 - 0x29d4];
    unsigned char unk_29D9;
};

void func_ov109_0229d514(struct UnkStruct_0229d514 *self)
{
    self->unk_29B4 = 0;
    func_ov094_0229af40((char *) self + 0xcc, 2);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    self->unk_29D1 = 0x10;
    func_ov002_02209e18((char *) self + 0x225c);
    self->unk_29CF = 0;
    self->unk_29D3 = 0;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    self->unk_29D9 = 0;
}