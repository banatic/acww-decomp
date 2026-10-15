/* func_ov068_0226f504 @ 0x0226f504, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226f504 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x26c - 0x68];
    int unk_26C;
    unsigned char pad_270[0x30c - 0x270];
    int unk_30C;
    unsigned char pad_310[0x396 - 0x310];
    short unk_396;
};

extern void func_020e8b60(void *, int, int, int);
extern int func_02034270(void *, void *, int, int);
extern int FX_MulFunc(int, int);
extern void func_020ee470(void *);
extern void func_ov068_0226fd80(void *);
extern void func_0203423c(void *);
extern short FX_SinCosTable_[][2];

void func_ov068_0226f504(struct UnkStruct_0226f504 *self)
{
    unsigned char buf[0x40];
    int val;

    val = self->unk_26C;
    val = val + (val >> 1);
    func_020e8b60((char *) self + 0x270, val, 0x200, val);

    func_02034270(buf, (char *) self + 0x5c, 0, 0);

    {
        int *out = (int *) (buf + 0x24);
        self->unk_5C = self->unk_5C + (out[0] >> 5);
        self->unk_64 = self->unk_64 + (out[2] >> 5);
    }

    self->unk_26C = FX_MulFunc(self->unk_26C, 0xfd7);

    self->unk_30C = FX_MulFunc(0x100, FX_SinCosTable_[(unsigned short) self->unk_396 >> 4][0]);

    self->unk_396 = (short) (self->unk_396 + 0x400);

    if (self->unk_26C < 0x80) {
        self->unk_26C = 0;
        func_020ee470(self);
    }

    func_ov068_0226fd80(self);

    self->unk_60 = *(int *) (buf + 0x3c) - self->unk_26C - 0x200;

    func_0203423c(buf);
}
