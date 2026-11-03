/* museum_insect_motions_8: 3 functions, module ov004
 * mwccarm 1.2/base -O1,s
 * func_ov004_022450d4 @ 0x022450d4, 0xa0 bytes, Thumb
 * func_ov004_02245050 @ 0x02245050, 0x84 bytes, Thumb
 * func_ov004_02244fcc @ 0x02244fcc, 0x84 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022450d4 {
    char unk_00[0x178];
    Vec3 arm[2];
    char unk_190[0x196 - 0x190];
    unsigned char unk_196;
} UnkStruct_022450d4;

typedef struct UnkStruct_02245050 {
    char unk_00[0x178];
    Vec3 arm[2];
    char unk_190[0x192 - 0x190];
    short ang;
    char unk_194[0x2cc - 0x194];
    int posy;
} UnkStruct_02245050;

typedef struct UnkStruct_02244fcc {
    char unk_00[0x2c8];
    Vec3 pos;
} UnkStruct_02244fcc;

extern int func_02034270(void *w, Vec3 *v, int a, int b);
extern int func_020341c8(void *w, int a);
extern void func_0203423c(void *w);
extern int func_ov004_02244e38(UnkStruct_022450d4 *self, Vec3 *p);
extern void *func_02032c64(void *ctx);
extern void *func_02032c50(void *ctx);
extern void func_02031288(void *ctx, Vec3 *a, Vec3 *b, int ang, int r, void *o, int k);
extern short FX_SinCosTable_[];

int func_ov004_022450d4(UnkStruct_022450d4 *self)
{
    char w1[0x40];
    char w2[0x40];
    unsigned char n, kind;
    int d;
    Vec3 *q;

    kind = self->unk_196;
    n = 0;
    q = self->arm;
    func_02034270(w1, q, 0, 1);
    d = func_020341c8(w1, 1);
    func_0203423c(w1);
    if (d <= 0 || d > q->y || (kind == 0x1e && func_ov004_02244e38(self, q) != 0)) {
        n = n + 1;
    }
    func_02034270(w2, q + 1, 0, 1);
    d = func_020341c8(w2, 1);
    func_0203423c(w2);
    if (d <= 0 || d > q[1].y || (kind == 0x1e && func_ov004_02244e38(self, q + 1) != 0)) {
        n = n + 2;
    }
    return n;
}

int func_ov004_02245050(UnkStruct_02245050 *self)
{
    char buf[0x30];
    unsigned char n;
    Vec3 *q;
    int y;
    short ang;

    n = 0;
    q = self->arm;
    y = self->posy;
    func_02032c64(buf);
    ang = self->ang;
    func_02031288(buf, q, q, ang, 0x266, 0, 0xb);
    if (q[0].y > y) {
        n = n + 1;
    }
    func_02031288(buf, &q[1], &q[1], ang, 0x266, 0, 0xb);
    if (q[1].y > y) {
        n = n + 2;
    }
    func_02032c50(buf);
    return n;
}

void func_ov004_02244fcc(UnkStruct_02244fcc *self)
{
    Vec3 *p, *q;
    short ang;
    int i, x, y, z;

    p = &self->pos;
    ang = *(short *) ((char *) self + 0x192);
    q = (Vec3 *) ((char *) self + 0x178);
    i = ((unsigned short) (short) (ang + 0xe38) >> 4) << 1;
    z = p->z + FX_SinCosTable_[i + 1];
    y = p->y;
    x = p->x + FX_SinCosTable_[i];
    q[0].x = x;
    q[0].y = y;
    q[0].z = z;
    i = ((unsigned short) (short) (ang - 0xe38) >> 4) << 1;
    z = p->z + FX_SinCosTable_[i + 1];
    y = p->y;
    x = p->x + FX_SinCosTable_[i];
    q[1].x = x;
    q[1].y = y;
    q[1].z = z;
}
