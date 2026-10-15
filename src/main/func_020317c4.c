/* func_020317c4 @ 0x020317c4, 0x150 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020317c4 {
    int x, y, z;
} UnkStruct_020317c4;

extern int func_02031b38(int a, int b);
extern int func_02031a74(int a, int b);
extern int func_020310d0(UnkStruct_020317c4 *v, int z, int k);
extern int func_020345e0(int *out, UnkStruct_020317c4 *v, int z);

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
