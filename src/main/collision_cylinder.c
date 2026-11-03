/* collision_cylinder: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02030324 @ 0x02030324, 0x1b0 bytes, Thumb
 * func_0203021c @ 0x0203021c, 0x106 bytes, Thumb
 * func_0203006c @ 0x0203006c, 0x1b0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int x, y, z;
    int r;
    int h;
} Cyl;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct UnkStruct_0203021c {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0203021c;

extern int func_020306a4(Cyl *c, Vec3 *p);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern int FX_Sqrt(int a);
extern int func_020ea838(const VecFx32 *v);

int func_02030324(Cyl *cyl, Vec3 *pt, Vec3 *org)
{
    Vec3 v[6];
    int a, b, cc;
    int q1, q2, q3;
    int disc, s;
    int t1, t2;
    int hi;
    int px, py, pz;
    int px2, py2, pz2;
    int ax, ay, az;
    int rad, hh;
    int m1, m2;

    if (func_020306a4(cyl, org) != 0) {
        goto fail;
    }

    az = org->z;
    ay = org->y;
    ax = org->x;
    v[0].x = ax;
    v[0].y = ay;
    v[0].z = az;
    az = pt->z;
    ay = pt->y;
    ax = pt->x;
    v[1].x = ax;
    v[1].y = ay;
    v[1].z = az;
    az = cyl->z;
    ay = cyl->y;
    ax = cyl->x;
    v[2].x = ax;
    v[2].y = ay;
    v[2].z = az;
    rad = cyl->r;
    hh = cyl->h;

    func_020eaca0(&v[3], &v[1], &v[0]);

    m1 = FX_MulFunc(v[3].z, v[3].z);
    m2 = FX_MulFunc(v[3].x, v[3].x);
    a = m2 + m1;
    if ((a < 0 ? -a : a) < 4) {
        return 0;
    }

    b = FX_MulFunc(v[3].x, v[0].x - v[2].x);
    b = b + FX_MulFunc(v[3].z, v[0].z - v[2].z);
    b = FX_Div(b, a) << 1;

    q1 = FX_MulFunc(v[0].z - v[2].z, v[0].z - v[2].z);
    q2 = FX_MulFunc(v[0].x - v[2].x, v[0].x - v[2].x);
    q3 = FX_MulFunc(rad, rad);
    cc = FX_Div(q2 + q1 - q3, a);

    disc = FX_MulFunc(b, b) - (cc << 2);
    if (disc < 0) {
        return 0;
    }
    s = FX_Sqrt(disc);
    if (s < 0) {
        s = -s;
    }
    t1 = -(b + s) >> 1;
    t2 = (s - b) >> 1;

    hi = v[2].y + hh;

    if ((t1 < 0 ? -t1 : t1) < 4 || (t1 >= 0 && t1 <= 0x1000)) {
        pz = v[0].z + FX_MulFunc(t1, v[3].z);
        py = v[0].y + FX_MulFunc(t1, v[3].y);
        px = v[0].x + FX_MulFunc(t1, v[3].x);
        if (py <= hi) {
            pt->x = px;
            pt->y = py;
            pt->z = pz;
            return 1;
        }
    }
    if ((t2 < 0 ? -t2 : t2) < 4 || (t2 >= 0 && t2 <= 0x1000)) {
        pz2 = org->z + FX_MulFunc(t2, v[3].z);
        py2 = org->y + FX_MulFunc(t2, v[3].y);
        px2 = org->x + FX_MulFunc(t2, v[3].x);
        if (py2 <= hi) {
            pt->x = px2;
            pt->y = py2;
            pt->z = pz2;
            return 1;
        }
    }
fail:
    return 0;
}

static __inline void VEC_Set(VecFx32 *p, fx32 x, fx32 y, fx32 z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

int func_0203021c(UnkStruct_0203021c *p0, VecFx32 *p1, const VecFx32 *p2)
{
    fx32 d;
    fx32 d2;
    VecFx32 a;
    VecFx32 b;
    VecFx32 v;
    VecFx32 w;
    VecFx32 w2;
    fx32 t;
    fx32 lim;

    VEC_Set(&a, p2->x, p2->y, p2->z);
    VEC_Set(&b, p1->x, p1->y, p1->z);
    func_020eaca0((Vec3 *) (&v), (Vec3 *) (&b), (Vec3 *) (&a));
    if (func_020ea838(&v)) {
        t = (v.y < 0) ? -v.y : v.y;
        if (t >= 4) {
            lim = p0->unk_04 + p0->unk_10;
            if (a.y > lim && b.y < lim) {
                d = (fx32) FX_Div((fx32) (lim - a.y), (fx32) v.y);
                VEC_Set(&w, a.x + (fx32) FX_MulFunc((fx32) v.x, (fx32) d), a.y + (fx32) FX_MulFunc((fx32) v.y, (fx32) d), a.z + (fx32) FX_MulFunc((fx32) v.z, (fx32) d));
                if (func_020306a4((Cyl *) p0, (Vec3 *) (&w))) {
                    p1->x = w.x;
                    p1->y = w.y;
                    p1->z = w.z;
                    return 1;
                }
            } else if (a.y < 0 && b.y > 0) {
                d2 = (fx32) FX_Div((fx32) (-a.y), (fx32) v.y);
                VEC_Set(&w2, a.x + (fx32) FX_MulFunc((fx32) v.x, (fx32) d2), a.y + (fx32) FX_MulFunc((fx32) v.y, (fx32) d2), a.z + (fx32) FX_MulFunc((fx32) v.z, (fx32) d2));
                if (func_020306a4((Cyl *) p0, (Vec3 *) (&w2))) {
                    p1->x = w2.x;
                    p1->y = w2.y;
                    p1->z = w2.z;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int func_0203006c(Cyl *cyl, Vec3 *pt, Vec3 *org)
{
    Vec3 v[6];
    int a, b, cc;
    int q1, q2, q3;
    int disc, s;
    int t1, t2;
    int lo, hi;
    int px, py, pz;
    int ax, ay, az;
    int rad;
    int m1, m2;

    if (func_020306a4(cyl, org) != 0) {
        goto fail;
    }

    az = org->z;
    ay = org->y;
    ax = org->x;
    v[0].x = ax;
    v[0].y = ay;
    v[0].z = az;
    az = pt->z;
    ay = pt->y;
    ax = pt->x;
    v[1].x = ax;
    v[1].y = ay;
    v[1].z = az;
    az = cyl->z;
    ay = cyl->y;
    ax = cyl->x;
    v[2].x = ax;
    v[2].y = ay;
    v[2].z = az;
    rad = cyl->r;

    func_020eaca0(&v[3], &v[1], &v[0]);

    m1 = FX_MulFunc(v[3].z, v[3].z);
    m2 = FX_MulFunc(v[3].x, v[3].x);
    a = m2 + m1;
    if ((a < 0 ? -a : a) < 4) {
        return 0;
    }

    b = FX_MulFunc(v[3].x, v[0].x - v[2].x);
    b = b + FX_MulFunc(v[3].z, v[0].z - v[2].z);
    b = FX_Div(b, a) << 1;

    q1 = FX_MulFunc(v[0].z - v[2].z, v[0].z - v[2].z);
    q2 = FX_MulFunc(v[0].x - v[2].x, v[0].x - v[2].x);
    q3 = FX_MulFunc(rad, rad);
    cc = FX_Div(q2 + q1 - q3, a);

    disc = FX_MulFunc(b, b) - (cc << 2);
    if (disc < 0) {
        return 0;
    }
    s = FX_Sqrt(disc);
    if (s < 0) {
        s = -s;
    }
    t1 = -(b + s) >> 1;
    t2 = (s - b) >> 1;

    lo = cyl->y;
    hi = lo + cyl->h;

    if ((t1 < 0 ? -t1 : t1) < 4 || (t1 >= 0 && t1 <= 0x1000)) {
        pz = v[0].z + FX_MulFunc(t1, v[3].z);
        py = v[0].y + FX_MulFunc(t1, v[3].y);
        px = v[0].x + FX_MulFunc(t1, v[3].x);
        if (py >= lo && py <= hi) {
            pt->x = px;
            pt->y = py;
            pt->z = pz;
            return 1;
        }
    }
    if ((t2 < 0 ? -t2 : t2) < 4 || (t2 >= 0 && t2 <= 0x1000)) {
        pz = v[0].z + FX_MulFunc(t2, v[3].z);
        py = v[0].y + FX_MulFunc(t2, v[3].y);
        px = v[0].x + FX_MulFunc(t2, v[3].x);
        if (py >= lo && py <= hi) {
            pt->x = px;
            pt->y = py;
            pt->z = pz;
            return 1;
        }
    }
fail:
    return 0;
}
