/* touch_pick_shapes_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b8550 @ 0x020b8550, 0x11c bytes, Thumb
 * func_020b8538 @ 0x020b8538, 0x18 bytes, Thumb
 * func_020b83ec @ 0x020b83ec, 0x14c bytes, Thumb
 * func_020b8314 @ 0x020b8314, 0xd8 bytes, Thumb
 * func_020b82ec @ 0x020b82ec, 0x28 bytes, Thumb
 * func_020b82d0 @ 0x020b82d0, 0x1c bytes, Thumb
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b, c, d, e;
} UnkStruct_020b83ec;

typedef struct {
    int m[12];
} Mtx;

typedef struct {
    Vec3 a, b, c;
} UnkStruct_020b8314;

typedef struct {
    Vec3 a;
    Vec3 b;
} Pair;

extern int FX_MulFunc(int a, int b);
extern void *func_02030678(void *w, Vec *v, int a, int b);
extern int func_0203006c(void *w, Vec *a, Vec *b);
extern int func_02030668(void *w);
extern short data_0213a59c[];
extern short data_0213c59c[];
extern unsigned char data_020d2254[];
extern short FX_SinCosTable_[];
extern int func_0203f8d0(Vec3 *out, void *p);
extern int func_0203021c(UnkStruct_020b83ec *obj, Vec3 *a, Vec3 *b);
extern void func_020ea78c(Vec3 *v, int ang);
extern int data_021c67a4;
extern int data_020ca0e8;
extern Mtx data_0213fee4;
extern int func_0203c53c(int v);
extern int FX_Div(int a, int b);
extern int func_020ea838(Vec3 *v);
extern void func_020eabc8(Vec3 *v, int s);
extern void func_01ffd070(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int MTX_Inverse43(Mtx *a, Mtx *b);
extern void MTX_MultVec43(Vec3 *v, Mtx *m, Vec3 *dst);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern void *func_020b8020(void *);
extern void *func_020b8038(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

int func_020b8550(Vec *out, Vec *p, Vec *q, int a4, int a5)
{
    Vec v0;
    Vec a;
    int val;
    Vec b;
    unsigned char w[0x20];
    int sn;
    int cs;
    int x;
    int y;
    int z;
    v0.x = 0;
    v0.y = 0;
    v0.z = 0;
    func_02030678(w, &v0, a4, a5);
    z = p->z;
    y = p->y;
    x = p->x;
    a.x = x;
    a.y = y;
    a.z = z;
    z = q->z;
    y = q->y;
    x = q->x;
    b.x = x;
    b.y = y;
    b.z = z;
    sn = data_0213a59c[0];
    cs = data_0213a59c[1];
    x = a.x;
    y = (val = a.y);
    a.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
    a.y = FX_MulFunc(sn, x) + FX_MulFunc(cs, y);
    y = b.y;
    x = b.x;
    b.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
    b.y = FX_MulFunc(sn, x) + FX_MulFunc(((((((cs)))))), y);
    if (func_0203006c(w, &b, &a) != 0) {
        y = b.y;
        sn = data_0213c59c[0];
        x = b.x;
        cs = data_0213c59c[1];
        b.x = FX_MulFunc(cs, x) - FX_MulFunc(sn, y);
        b.y = FX_MulFunc(sn, x) + FX_MulFunc(cs, y);
        if (1) {
            out->x = b.x;
            out->y = b.y;
        }
        out->z = b.z;
        func_02030668(w);
        return 1;
    }
    func_02030668(w);
    return 0;
}

unsigned char func_020b8538(int r0)
{
    if (r0 < 0) {
        goto out;
    }
    if (r0 >= 23) {
        goto out;
    }
    return data_020d2254[r0];
out:
    return 0;
}

int func_020b83ec(Vec3 *self, Vec3 *b, void *p2, int p3, int p4)
{
    Vec3 v0;
    Vec3 A;
    Vec3 B;
    Vec3 C;
    UnkStruct_020b83ec obj;
    int ang;
    short sh;
    unsigned short u;
    int k;
    int s, c;
    int z, y;
    int z2, y2;
    int z3, y3;

    ang = func_0203f8d0(&v0, p2);

    z = b->z;
    y = b->y;
    A.x = b->x;
    A.y = y;
    A.z = z;
    {
        int t2 = self->z, t1 = self->y, t0 = self->x;
        B.x = t0;
        B.y = t1;
        B.z = t2;
    }
    C.x = v0.x;
    C.y = v0.y;
    C.z = v0.z;

    sh = (short) (-ang);
    u = (unsigned short) sh;
    k = (u >> 4) * 2;
    s = FX_SinCosTable_[k];
    c = FX_SinCosTable_[k + 1];

    A.y = FX_MulFunc(c, y) - FX_MulFunc(s, z);
    A.z = FX_MulFunc(s, y) + FX_MulFunc(c, z);

    z2 = B.z;
    y2 = B.y;
    B.y = FX_MulFunc(c, y2) - FX_MulFunc(s, z2);
    B.z = FX_MulFunc(s, y2) + FX_MulFunc(c, z2);

    z3 = C.z;
    y3 = C.y;
    C.y = FX_MulFunc(c, y3) - FX_MulFunc(s, z3);
    C.z = FX_MulFunc(s, y3) + FX_MulFunc(c, z3);

    func_02030678((void *) (&obj), (Vec *) (&C), p3, p4);
    if (func_0203021c(&obj, &B, &A) != 0 || func_0203006c((void *) (&obj), (Vec *) (&B), (Vec *) (&A)) != 0) {
        func_020ea78c(&B, ang);
        {
            int u2 = B.z, u1 = B.y, u0 = B.x;
            self->x = u0;
            self->y = u1;
            self->z = u2;
        }
        func_02030668((void *) (&obj));
        return 1;
    }
    func_02030668((void *) (&obj));
    return 0;
}

void func_020b8314(UnkStruct_020b8314 *out, int px, int pz)
{
    Vec3 zero;
    Pair pr;
    Vec3 v2;
    Vec3 ra;
    Vec3 rb;
    Mtx m;
    Vec3 d;
    int s;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    s = -FX_Div(0x60000, func_0203c53c(data_021c67a4));
    pr.a.x = (px << 12) - 0x80000;
    pr.a.y = -((pz << 12) - 0x60000);
    pr.a.z = s;
    pr.b.x = (px << 12) - 0x80000;
    pr.b.y = -((pz << 12) - 0x60000);
    pr.b.z = s;
    func_020ea838(&pr.b);
    func_020eabc8(&pr.b, data_020ca0e8);
    func_01ffd070(&v2, &zero, &pr.b);
    m = data_0213fee4;
    MTX_Inverse43(&m, &m);
    MTX_MultVec43(&zero, &m, &ra);
    MTX_MultVec43(&v2, &m, &rb);
    out->a.x = ra.x;
    out->a.y = ra.y;
    out->a.z = ra.z;
    out->b.x = rb.x;
    out->b.y = rb.y;
    out->b.z = rb.z;
    func_020eaca0(&d, &out->b, &out->a);
    out->c.x = d.x;
    out->c.y = d.y;
    out->c.z = d.z;
    func_020ea838(&out->c);
}

void *func_020b82ec(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 10, 0x44, (((void (*)(void *)) func_020b8038)), (((void (*)(void *)) func_020b8020)));
    return arg;
}

void *func_020b82d0(void *param)
{
    __cxa_vec_cleanup((void *) (param), 0xa, 0x44, (((void (*)(void *)) func_020b8020)));
    return param;
}
