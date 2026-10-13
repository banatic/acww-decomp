/* func_020c13bc @ 0x020c13bc, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;
extern int func_020644cc(int n);
extern int data_020e5978;
extern struct {
    unsigned char pad[0x54];
    int f54;
} data_021fba48;
extern short data_021f8ab0[];
extern short FX_SinCosTable_[];
typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x34 - 0x10];
    VecFx32 pos;
    VecFx32 vel;
    unsigned char pad_4C[0x50 - 0x4c];
    int unk_50;
    unsigned short f54;
    unsigned char pad_56[0x58 - 0x56];
    int unk_58;
    unsigned char pad_5C[0x60 - 0x5c];
    int unk_60;
} UnkStruct_020c13bc;
void func_020c13bc(UnkStruct_020c13bc *self, int flag)
{
    int v;
    int r;
    int m;
    int vy;
    int t;
    int k;
    unsigned short ang;
    int i;
    int kk;
    int d;
    int n;
    VecFx32 *p;
    r = func_020644cc(0x8a);
    v = ((data_020e5978 * r) + 0x80) << 12;
    data_020e5978 *= -1;
    vy = ((int) 0xfffec000) - (func_020644cc(0x10) << 12);
    p = &self->pos;
    self->pos.x = v;
    p->y = vy;
    p->z = 0;
    m = data_021fba48.f54;
    d = func_020644cc(0xaac) - 0x556;
    t = (d + data_021f8ab0[0x1c]) * m;
    ang = (unsigned short) ((t << 4) >> 16);
    i = ang >> 4;
    kk = i * 2;
    p = &self->vel;
    self->vel.x = (-0x24) * FX_SinCosTable_[kk];
    p->y = 0x24 * FX_SinCosTable_[kk + 1];
    p->z = 0;
    self->unk_50 = 0x800;
    self->f54 = (unsigned short) ((t << 4) >> 16);
    k = func_020644cc(3);
    self->unk_0C = k + 2;
    switch (k) {
        case 0:
            n = func_020644cc(0x40) + 0x80;
            break;

        case 1:
            n = func_020644cc(0x40) + 0x40;
            break;

        default:
            n = func_020644cc(0x40);
            break;
    }

    self->unk_60 = n;
    if (flag == 1) {
        self->pos.y = self->pos.y + (func_020644cc(n + 0x101) << 12);
    }
    self->unk_58 = 2;
}
