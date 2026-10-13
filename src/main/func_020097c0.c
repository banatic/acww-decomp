/* func_020097c0 @ 0x020097c0, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14;
} UnkStruct_020097c0;
typedef struct {
    char pad_00[0x5c];
    int unk_5C, unk_60, unk_64;
    char pad_68[0x8e - 0x68];
    short unk_8E;
    char pad_90[0x7d4 - 0x90];
    UnkStruct_020097c0 w;
} UnkStruct_020097c0_2;

extern short FX_SinCosTable_[];

extern int func_0200f290(UnkStruct_020097c0_2 *self, int k);
extern int func_020b65c4(void);
extern int FX_MulFunc(int a, int b);
extern int func_020ea9c8(Vec3 *v);
extern void func_02011490(int *p, int v);
extern int func_020ea990(Vec3 *a, Vec3 *b);
extern int func_02011398(int v);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int a, int b);
extern void func_020113e0(short *h, int m);
extern void func_020110a0(UnkStruct_020097c0_2 *self, short *h);
extern void func_0201107c(UnkStruct_020097c0_2 *self, int *p);

int func_020097c0(UnkStruct_020097c0_2 *self)
{
    UnkStruct_020097c0 *w;
    int *m;
    int saved;
    int ret;
    int lim;
    short hv;
    int r;
    Vec3 d;
    Vec3 p;
    Vec3 *sv;
    int idx;
    int t;
    int e;

    w = &self->w;
    m = &w->unk_0C;
    saved = w->unk_10;
    ret = 0;
    sv = (Vec3 *) &self->unk_5C;
    p.x = self->unk_5C;
    p.y = sv->y;
    p.z = sv->z;
    if (func_0200f290(self, 0x18) != 0) {
        w->unk_00 = self->unk_5C;
    }
    if (func_020b65c4() == 0x20 && w->unk_14 == 0x40 && p.z >= w->unk_08) {
        w->unk_08 = p.z;
    }
    d.x = w->unk_00 - self->unk_5C;
    d.z = w->unk_08 - self->unk_64;
    lim = FX_MulFunc(0x4000, *m);
    if (lim < 0x1000) {
        lim = 0x1000;
    }
    if (func_020ea9c8(&d) < lim) {
        if (*m <= 0x333) {
            func_02011490(&self->unk_5C, w->unk_00);
            func_02011490(&self->unk_64, w->unk_08);
            if (w->unk_00 == self->unk_5C && w->unk_08 == self->unk_64) {
                *m = 0;
                ret = 1;
            } else {
                *m = func_020ea990((Vec3 *) &self->unk_5C, &p);
                sv = (Vec3 *) &self->unk_5C;
                self->unk_5C = p.x;
                sv->y = p.y;
                sv->z = p.z;
            }
        } else {
            *m = func_02011398(*m);
        }
    } else {
        *m = func_020113b0(*m, saved);
    }
    r = func_020e8ed8(d.x, d.z);
    hv = self->unk_8E;
    if (*m != 0) {
        func_020113e0(&hv, r);
        func_020110a0(self, &hv);
    }
    idx = ((unsigned short) (short) (hv - r)) >> 4;
    t = FX_MulFunc(*m, FX_SinCosTable_[idx * 2 + 1]);
    if (t < 0) {
        t = -t;
    }
    e = t;
    func_0201107c(self, &e);
    return ret;
}
