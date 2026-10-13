/* func_0203c40c @ 0x0203c40c, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_InvA(int);
extern int FX_MulFunc(int, int);
extern void func_0203a958(void *, int, int, int, int);
extern short FX_SinCosTable_[];
extern int data_021f6a6c;

typedef struct {
    unsigned char pad_00[0x90];
    int unk_90;
    int unk_94;
    short unk_98;
    unsigned char pad_9A[0x1b0 - 0x9a];
    int unk_1B0;
    int unk_1B4;
    int unk_1B8;
    int unk_1BC;
    int unk_1C0;
    int unk_1C4;
    short unk_1C8;
} UnkStruct_0203c40c;

void func_0203c40c(UnkStruct_0203c40c *self, short val)
{
    int sum1, sum2;
    unsigned int u1, u2;
    int i, j;
    int arg5;

    self->unk_1C8 = val;

    sum1 = (int) self->unk_1C8 + (int) self->unk_98;
    u1 = (unsigned int) ((sum1 << 16) >> 1);
    u2 = u1 >> 16;
    i = (int) u2 >> 4;
    self->unk_1BC = FX_SinCosTable_[2 * i];

    sum2 = (int) self->unk_1C8 + (int) self->unk_98;
    u1 = (unsigned int) ((sum2 << 16) >> 1);
    u2 = u1 >> 16;
    j = (int) u2 >> 4;
    self->unk_1C0 = FX_SinCosTable_[2 * j + 1];

    self->unk_1C4 = FX_MulFunc(self->unk_1BC, FX_InvA(self->unk_1C0));

    arg5 = self->unk_1B8 + self->unk_94;
    func_0203a958(&data_021f6a6c, self->unk_1B0, (short) (self->unk_1C8 + self->unk_98), self->unk_1B4 + self->unk_90, arg5);
}
