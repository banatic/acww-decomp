/* func_020b83ec @ 0x020b83ec, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b, c, d, e;
} UnkStruct_020b83ec;

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int func_0203f8d0(Vec3 *out, void *p);
extern void *func_02030678(UnkStruct_020b83ec *obj, Vec3 *v, int c, int d);
extern int func_0203021c(UnkStruct_020b83ec *obj, Vec3 *a, Vec3 *b);
extern int func_0203006c(UnkStruct_020b83ec *obj, Vec3 *a, Vec3 *b);
extern int func_02030668(UnkStruct_020b83ec *obj);
extern void func_020ea78c(Vec3 *v, int ang);

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

    func_02030678(&obj, &C, p3, p4);
    if (func_0203021c(&obj, &B, &A) != 0 || func_0203006c(&obj, &B, &A) != 0) {
        func_020ea78c(&B, ang);
        {
            int u2 = B.z, u1 = B.y, u0 = B.x;
            self->x = u0;
            self->y = u1;
            self->z = u2;
        }
        func_02030668(&obj);
        return 1;
    }
    func_02030668(&obj);
    return 0;
}
