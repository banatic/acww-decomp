/* func_ov003_02221cb4 @ 0x02221cb4, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];
extern void func_01ffd070(int *out, void **src, int *mat);

typedef struct UnkStruct_02221cb4 {
    char pad_00[0x18];
    int out_x;
    int out_y;
    int out_z;
    char pad_24[0x48 - 0x24];
    unsigned short unk_48;
    char pad_4A[0x50 - 0x4A];
    short unk_50;
    char pad_52[0x54 - 0x52];
    void *unk_54;
} UnkStruct_02221cb4;

extern void func_ov003_02222860(UnkStruct_02221cb4 *self);

void func_ov003_02221cb4(UnkStruct_02221cb4 *self)
{
    int a, b;
    int mat[3];
    int out[3];

    self->unk_50 += 0x2000;

    a = FX_SinCosTable_[2 * ((unsigned short) self->unk_50 >> 4)] >> 1;
    b = FX_SinCosTable_[2 * ((unsigned short) self->unk_48 >> 4)];

    mat[0] = (a * b) >> 12;
    mat[1] = 0;
    mat[2] = (FX_SinCosTable_[2 * ((unsigned short) self->unk_48 >> 4) + 1] * a) >> 12;

    func_01ffd070(out, &self->unk_54, mat);

    self->out_x = out[0];
    self->out_y = out[1];
    self->out_z = out[2];

    if (self->unk_50 < 0) {
        func_ov003_02222860(self);
    }
}
