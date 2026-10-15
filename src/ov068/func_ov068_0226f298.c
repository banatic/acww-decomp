/* func_ov068_0226f298 @ 0x0226f298, 0xb0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
extern int func_ov003_0221a35c(void *, int);
extern int data_ov068_022786b8;
extern int data_ov068_022786bc;

struct UnkStruct_0226f298 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x288];
    int unk_2F0;
    int unk_2F4;
    unsigned char pad_2F8[0x8c];
    int unk_384;
};

void func_ov068_0226f298(struct UnkStruct_0226f298 *self)
{
    int *p = &self->unk_2F4;
    int diff;

    *p += FX_Div(0, 0x3e8000) + 0x158;
    self->unk_5C += self->unk_2F0;
    self->unk_64 += *p;

    diff = self->unk_64 - self->unk_384;
    if (diff < 0) {
        diff = -diff;
    }

    self->unk_60 = -FX_MulFunc(diff, 0x3d7);

    if ((data_ov068_022786bc & 1) == 0) {
        data_ov068_022786b8 = FX_Div(0, 0x64000) + 0x3000;
        data_ov068_022786bc |= 1;
    }

    if (diff >= data_ov068_022786b8) {
        func_ov003_0221a35c(self, 6);
    }
}
