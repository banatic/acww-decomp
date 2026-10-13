/* func_0205fc3c @ 0x0205fc3c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} InnerStruct;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[4];
    int unk_10;
    char pad_14[20];
    InnerStruct *unk_28;
    char pad_2C[4];
    int unk_30;
} UnkStruct_0205fc3c;

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int, int);

void func_0205fc3c(UnkStruct_0205fc3c *self)
{
    int temp;
    int diff;
    int index;
    int base;
    int result;

    temp = (self->unk_30 * self->unk_30 * 0x4800) / 0xe1;
    diff = self->unk_28->unk_8E - temp;
    index = ((unsigned short) (short) diff) >> 4;
    base = index * 2;
    result = FX_MulFunc(FX_SinCosTable_[base], 0x2ee);
    self->unk_08 -= result;
    result = FX_MulFunc(FX_SinCosTable_[base + 1], 0x2ee);
    self->unk_10 -= result;
}
