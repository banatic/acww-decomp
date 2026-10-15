/* func_ov003_0221af94 @ 0x0221af94, 0xd0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char pad_60[0x64 - 0x60];
    unsigned int unk_64;
    unsigned char pad_68[0x26c - 0x68];
    unsigned int unk_26C;
    unsigned char pad_270[0x2a4 - 0x270];
    unsigned char unk_2A4[4];
    unsigned char pad_2A8[0x2b4 - 0x2a8];
    unsigned int unk_2B4;
    unsigned char pad_2B8[0x2bc - 0x2b8];
    unsigned int unk_2BC;
    unsigned char pad_2C0[0x2e0 - 0x2c0];
    unsigned char unk_2E0;
    unsigned char pad_2E1[0x2ec - 0x2e1];
    unsigned int unk_2EC;
    unsigned char pad_2F0[0x328 - 0x2f0];
    unsigned char unk_328[4];
    unsigned char pad_32C[0x36a - 0x32c];
    unsigned char unk_36A;
    unsigned char pad_36B[0x378 - 0x36b];
    unsigned short unk_378;
} UnkStruct_0221af94;

extern int func_02089cc0(void *a, int b);
extern int func_020044c0(void *a, int b, int c, int d);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

void func_ov003_0221af94(UnkStruct_0221af94 *self)
{
    if (self->unk_2E0 != 0) {
        if ((((unsigned int) self->unk_378 << 0x16) >> 0x1f) == 0) {
            self->unk_5C += self->unk_2B4;
            self->unk_64 += self->unk_2BC;
        }
        if (func_02089cc0(&self->unk_2A4, 4) != 0 && (int) self->unk_26C < 0xa00) {
            if (self->unk_36A == 0) {
                func_020044c0(&self->unk_328, 0x81c, 0x7f, 0);
            }
            self->unk_36A = 1;
        } else {
            self->unk_36A = 0;
        }
    } else {
        self->unk_36A = 0;
    }

    {
        int q = FX_Div(self->unk_26C - 0x800, 0xc00);
        int m = FX_MulFunc(q, 0x10cd);
        self->unk_2EC = (unsigned int) (m + 0xdec) << 2;
    }
}
