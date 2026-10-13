/* func_020600bc @ 0x020600bc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x08];
    int unk_08;
    unsigned char pad_0C[0x04];
    int unk_10;
    unsigned char pad_14[0x14];
    char *unk_28;
    unsigned char pad_2C[0x04];
    int unk_30;
} UnkStruct_020600bc;

extern void func_0205fc3c(UnkStruct_020600bc *s);
extern void func_0206026c(UnkStruct_020600bc *s, int arg);
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);

void func_020600bc(UnkStruct_020600bc *s)
{
    if (s->unk_30 < 15) {
        func_0205fc3c(s);
        return;
    } else if (s->unk_30 >= 21) {
        func_0206026c(s, 1);
        return;
    } else {
        short value0;
        short v;
        int idx;
        int base;

        value0 = *((short *) (s->unk_28 + 0x8e));
        v = value0 - 0x1838;
        idx = ((unsigned short) v) >> 4;
        base = idx * 2;
        s->unk_08 += FX_MulFunc(FX_SinCosTable_[base], 1600);
        s->unk_10 += FX_MulFunc(FX_SinCosTable_[base + 1], 1600);
    }
}
