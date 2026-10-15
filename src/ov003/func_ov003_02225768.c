/* func_ov003_02225768 @ 0x02225768, 0x280 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off
typedef struct {
    int x;
    int y;
    int z;
} Vec3;
typedef struct {
    int m[12];
} Mtx;
extern Vec3 data_ov003_02236b64[];
extern Vec3 data_ov003_02236b4c[];
extern int func_0204b7a0(void *b);
extern int func_0204b910(void *b);
extern void func_ov003_02225a90(void *g, void *b, Vec3 *t);
extern int func_ov003_02225da0(void *g, int id, Vec3 *pos, int k, Vec3 *sc, int p, int q, int r);
extern void func_ov003_022259e8(void *g, Vec3 *t, int c, int d);
extern void func_ov003_022251a4(void *g, char *p, Mtx m);
char *func_ov003_02225768(char *g, char *b, int c, int dd, Vec3 *v, Mtx m)
{
    int i;
    int i2;
    int sx;
    int sx2;
    int z2;
    int z;
    struct {
        Vec3 a;
        Vec3 a2;
        Vec3 tA;
        Vec3 tB;
        Vec3 p;
        Vec3 s;
        Vec3 tF;
        Vec3 p2;
    } o;
    int n;
    unsigned int ok;
    u16 id;
    char *r;
    Vec3 *t;
    int sy;
    int sz;
    n = func_0204b7a0(b);
    ok = 0;
    id = *((u16 *) b);
    if ((id >= 0x2f) && (id <= 0x56)) {
        ok = 1;
    }
    if (ok > 0) {
        if (func_0204b910(b) != 0) {
            o.tA.x = v->x;
            o.tA.y = v->y;
            o.tA.z = v->z;
            func_ov003_02225a90(g, b, &o.tA);
        }
        r = (g + 0x8c4) + (n * 0x9c);
    } else if ((id >= 0x57) && (id <= 0x5b)) {
        c = c ^ dd;
        c = c & 1;
        if (func_0204b910(b) != 0) {
            o.tB.x = v->x;
            o.tB.y = v->y;
            o.tB.z = v->z;
            func_ov003_02225a90(g, b, &o.tB);
        }
        r = g + 0x174;
        c = c * 0x3a8;
        r = (r + c) + (n * 0x9c);
    } else if (id == 0x69) {
        i = 0;
        z = 0;
        do {
            t = &data_ov003_02236b64[i];
            sx = v->x + t->x;
            o.a.x = sx;
            sy = v->y + t->y;
            o.a.y = sy;
            sz = v->z + t->z;
            o.a.z = sz;
            o.p.x = sx;
            o.p.y = sy;
            o.p.z = sz;
            o.s.x = 0x1000;
            o.s.y = 0x1000;
            o.s.z = 0x1000;
            func_ov003_02225da0(g, 0x1542, &o.p, 0x1f, &o.s, 0, 0, 0);
            i++;
        } while (i < 3);
        r = (g + 0x8c4) + (n * 0x9c);
    } else if ((id >= 0x6a) && (id <= 0x6c)) {
        r = (g + 0xc6c) + (n * 0x9c);
    } else if (id == 0x6d) {
        o.tF.x = v->x;
        o.tF.y = v->y;
        o.tF.z = v->z;
        func_ov003_022259e8(g, &o.tF, c, dd);
        r = (g + 0xc6c) + (n * 0x9c);
    } else if ((id >= 0x5d) && (id <= 0x61)) {
        r = (g + 0xc6c) + (n * 0x9c);
    } else if ((id >= 0xc8) && (id <= 0xcf)) {
        if (func_0204b910(b) != 0) {
            i2 = 0;
            ;
            do {
                t = &data_ov003_02236b4c[i2];
                sx2 = v->x + t->x;
                o.a2.x = sx2;
                sy = v->y + t->y;
                o.a2.y = sy;
                sz = v->z + t->z;
                o.a2.z = sz;
                o.p2.x = sx2;
                o.p2.y = sy;
                o.p2.z = sz;
                o.s.x = 0x1000;
                o.s.y = 0x1000;
                o.s.z = 0x1000;
                func_ov003_02225da0(g, 0x1548, &o.p2, 0x1f, &o.s, 0, 0, 0);
                i2++;
            } while (i2 < 2);
        }
        r = (g + 0x11e8) + (n * 0x9c);
    } else {
        r = g + 0x174;
        c = c ^ dd;
        c = c & 1;
        c = c * 0x3a8;
        r = (r + c) + (n * 0x9c);
    }
    func_ov003_022251a4(g, r, m);
    return r;
}
