/* func_ov004_0224497c @ 0x0224497c, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0224497c {
    char unk_00[0x54];
    int unk_54;
    char unk_58[0xa8 - 0x58];
    int unk_A8;
    char unk_AC[0x2c8 - 0xac];
    Vec3 pos;
} UnkStruct_0224497c;

extern int FX_MulFunc(int a, int b);
extern int FX_Div(int numer, int denom);
extern short FX_SinCosTable_[];

void func_ov004_0224497c(UnkStruct_0224497c *self, int ang, int c, int d)
{
    int v;
    Vec3 *p;

    p = &self->pos;
    v = FX_Div(FX_SinCosTable_[((unsigned short) ang >> 4) << 1], d);
    if (self->unk_54 != self->unk_A8) {
        c = FX_MulFunc(c, 0x800);
    }
    if ((v > 0 && p->y + v < c + self->unk_54) || (v < 0 && p->y + v > self->unk_54 - c)) {
        p->y = p->y + v;
    }
}
