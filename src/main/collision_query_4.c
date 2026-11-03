/* collision_query_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020317c4 @ 0x020317c4, 0x150 bytes, Thumb
 * func_020316fc @ 0x020316fc, 0xc6 bytes, Thumb
 * func_02031650 @ 0x02031650, 0xac bytes, Thumb
 * func_0203162c @ 0x0203162c, 0x22 bytes, Thumb
 * func_02031614 @ 0x02031614, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020317c4 {
    int x, y, z;
} UnkStruct_020317c4;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0x30];
    int unk_30;
    unsigned char pad_34[8];
    int unk_3C;
} Big;

extern int func_02031b38(int a, int b);
extern int func_02031a74(int a, int b);
extern int func_020310d0(UnkStruct_020317c4 *v, int z, int k);
extern int func_020345e0(int *out, UnkStruct_020317c4 *v, int z);
extern int func_02034270(Big *big, void *src, int c, int d);
extern void func_0203423c(Big *big);
extern void func_01ffd070(Vec3 *dst, void *mtx, Vec3 *src);
extern void func_020ea6e0(int *v, int angle);
extern int FX_MulFunc(int a, int b);

int func_020317c4(int p0, int p1, int p2, int p3, u8 flag)
{
    UnkStruct_020317c4 pts[2];
    UnkStruct_020317c4 w;
    int q[6];
    UnkStruct_020317c4 u;
    int q2[7];
    int e;
    int d;
    int r5;
    int t;
    int a;
    int f3;
    int f2;
    int f3b;
    int f2b;
    int ab;

    d = p0 - p2;
    if (d < 0) {
        d = -d;
    }
    if (d > 1) {
        return 0;
    }
    e = p1 - p3;
    if (e < 0) {
        e = -e;
    }
    if (e > 1) {
        return 0;
    }
    if (flag != 0) {
        if (func_02031b38(p2, p3) != 0) {
            if (func_02031a74(p2, p3) == 0) {
                goto ok;
            }
        }
        return 0;
    } else {
        if (func_02031b38(p2, p3) == 0) {
            return 0;
        }
    }
ok:
    pts[0].x = (p0 << 13) + 0x1000;
    pts[0].y = 0;
    pts[0].z = (p1 << 13) + 0x1000;
    pts[1].x = (p2 << 13) + 0x1000;
    pts[1].y = 0;
    pts[1].z = (p3 << 13) + 0x1000;
    d = d + e;
    r5 = func_020310d0(&pts[1], 0, 0x19);
    if (d == 1) {
        if (r5 == 0) {
            goto ret1;
        }
        return 0;
    }
    if (d != 2) {
        goto ret1;
    }
    w.x = pts[1].x;
    w.y = 0;
    w.z = pts[0].z;
    t = func_020310d0(&w, 0, 0x19);
    if (t == 0) {
        if (r5 == t) {
            func_020345e0(q, &w, 0);
            f3 = 0;
            f2 = 0;
            a = q[0];
            if (a == q[1] && a == q[2]) {
                f2 = 1;
            }
            if (f2 != 0) {
                if (a == q[3]) {
                    f3 = 1;
                }
            }
            if (f3 != 0) {
                return 1;
            }
        }
    }
    u.x = pts[0].x;
    u.y = 0;
    u.z = pts[1].z;
    t = func_020310d0(&u, 0, 0x19);
    if (t == 0) {
        if (r5 == t) {
            func_020345e0(q2, &u, 0);
            f3b = 0;
            f2b = 0;
            ab = q2[0];
            if (ab == q2[1] && ab == q2[2]) {
                f2b = 1;
            }
            if (f2b != 0) {
                if (ab == q2[3]) {
                    f3b = 1;
                }
            }
            if (f3b != 0) {
                return 1;
            }
        }
    }
    return 0;
ret1:
    return 1;
}

int func_020316fc(void *a, int d, int *out, int p3)
{
    Big t;
    Vec3 v;
    Big u;
    Vec3 dirs[8];
    int res;
    int i;
    Vec3 *p;

    func_02034270(&t, a, 0, p3);
    if (t.unk_30 != 0) {
        dirs[0].x = -d;
        dirs[0].y = 0;
        dirs[0].z = -d;
        p = &dirs[1];
        p->x = -d;
        p->y = 0;
        p->z = d;
        p = &dirs[2];
        p->x = d;
        p->y = 0;
        p->z = d;
        p = &dirs[3];
        p->x = d;
        p->y = 0;
        p->z = -d;
        p = &dirs[4];
        p->x = -d;
        p->y = 0;
        p->z = 0;
        p = &dirs[5];
        p->x = d;
        p->y = 0;
        p->z = 0;
        p = &dirs[6];
        p->x = 0;
        p->y = 0;
        p->z = d;
        p = &dirs[7];
        p->x = 0;
        p->y = 0;
        p->z = -d;
        res = 0;
        for (i = 0; i < 8; i++) {
            func_01ffd070(&v, a, &dirs[i]);
            func_02034270(&u, &v, 0, p3);
            if (u.unk_30 == 0) {
                func_0203423c(&u);
                func_0203423c(&t);
                return 0;
            }
            res = t.unk_3C;
            func_0203423c(&u);
        }
        if (out != 0) {
            *out = res;
        }
        func_0203423c(&t);
        return 1;
    }
    func_0203423c(&t);
    return 0;
}

int func_02031650(Vec3 *out, Vec3 *base, void *arr, int p4, unsigned int count, int p6, int p7)
{
    int scale;
    int ry;
    int rz;
    int t;
    int local;
    Vec3 vec;
    Vec3 result;
    int i;

    if (count >= 1) {
        scale = (unsigned int) arr / count;
        vec.x = 0;
        vec.y = 0;
        vec.z = 0x1000;
        func_020ea6e0((int *) &vec, p4);
        for (i = 0; i <= count; i++) {
            t = i * scale;
            rz = base->z + FX_MulFunc(vec.z, t);
            ry = base->y + FX_MulFunc(vec.y, t);
            result.x = base->x + FX_MulFunc(vec.x, t);
            result.y = ry;
            result.z = rz;
            if (func_020316fc((void *) (&result), p6, &local, p7) != 0) {
                out->x = result.x;
                out->y = result.y;
                out->z = result.z;
                out->y = local;
                return 1;
            }
        }
    }
    return 0;
}

int func_0203162c(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return func_02031650((Vec3 *) a1, (Vec3 *) a2, (void *) a4, a3, a6, a5, 2);
}

int func_02031614(int a)
{
    return func_020316fc((void *) a, 0x0a00, 0, 2);
}
