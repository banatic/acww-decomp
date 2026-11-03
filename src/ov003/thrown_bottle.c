/* thrown_bottle: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222c12c @ 0x0222c12c, 0x2 bytes, Thumb
 * func_ov003_0222bfe0 @ 0x0222bfe0, 0x14c bytes, Thumb
 * func_ov003_0222beec @ 0x0222beec, 0xf4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x30];
    unsigned char unk_30;
    char pad_31[3];
    Vec3 unk_34, unk_40, unk_4C;
    int unk_58;
    unsigned char unk_5C;
} UnkStruct_0222bfe0;

extern int func_ov003_0222796c(Vec3 *a, Vec3 *b, Vec3 *c);
extern int func_ov003_02228400(Vec3 *v, int k);
extern int func_ov003_02229428(Vec3 *v, Vec3 *a, Vec3 *b, int n, int p, int q);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern void func_02031288(UnkStruct_0222bfe0 *s, Vec3 *a, Vec3 *b, int r, int t, int u, int v);
extern void func_ov003_0222462c(int id, Vec3 *a, Vec3 *b, int p, int q, int r);
extern int data_ov003_0223bda8;
extern int data_ov003_0223bda4;
extern int func_ov003_0222c16c(char *o);
extern void func_ov003_0222803c(Vec3 *v, int a);

void func_ov003_0222c12c(void) {}

void func_ov003_0222bfe0(int unused, UnkStruct_0222bfe0 *s)
{
    Vec3 *p34 = &s->unk_34;
    int *p58 = &s->unk_58;
    Vec3 *q;
    int py, pz, px;
    int x, y, z;
    volatile Vec3 a, b;
    Vec3 c, d, e, f, g, h, k;
    int t, ok;

    q = &s->unk_40;
    x = q->x;
    a.x = x;
    y = q->y;
    a.y = y;
    z = q->z;
    a.z = z;
    q = &s->unk_4C;
    px = q->x;
    b.x = px;
    py = q->y;
    b.y = py;
    pz = q->z;
    b.z = pz;
    c.x = p34->x;
    c.y = p34->y;
    c.z = p34->z;
    d.x = x;
    d.y = y;
    d.z = z;
    e.x = px;
    e.y = py;
    e.z = pz;
    if (func_ov003_0222796c(&c, &d, &e)) {
        s->unk_30 = 2;
        *p58 = 0;
        if (s->unk_5C != 0) {
            func_ov003_02228400(p34, 0x2800);
        }
        return;
    }
    f.x = a.x;
    f.y = a.y;
    f.z = a.z;
    g.x = b.x;
    g.y = b.y;
    g.z = b.z;
    ok = (func_ov003_02229428(p34, &f, &g, *p58, 0x14cd, 0xf) == 0);
    if (ok) {
        s->unk_30 = 2;
        *p58 = 0;
        if (s->unk_5C != 0) {
            func_ov003_02228400(p34, 0x2800);
        }
    }
    t = (*p58 * 0x199a) >> 5;
    if (t > 0x199a) {
        t = 0x199a;
    }
    func_02031288(s, p34, p34, func_0200322c(&s->unk_4C, &s->unk_40), t, 0, 0xb);
    h.x = p34->x;
    h.y = p34->y;
    h.z = p34->z;
    k.x = 0x1000;
    k.y = 0x1000;
    k.z = 0x1000;
    func_ov003_0222462c(0x1520, &h, &k, 0, 0, 0);
    *p58 = *p58 + 1;
}

void func_ov003_0222beec(void *unused, char *o)
{
    Vec3 v1;
    Vec3 s;
    Vec3 v2;
    Vec3 *p = (Vec3 *) (o + 0x34);
    int *n = (int *) (o + 0x58);
    int t;
    if (*n < 0x64) {
        v1.x = p->x;
        v1.y = p->y;
        v1.z = p->z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_0222462c(0x1520, &v1, &s, 0, 0, 0);
        if (func_ov003_0222c16c(o)) {
            *n = 0x64;
        }
    } else if (*n & 1) {
        v2.x = p->x;
        v2.y = p->y;
        v2.z = p->z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_0222462c(0x1520, &v2, &s, 0, 0, 0);
    }
    func_ov003_0222803c(p, data_ov003_0223bda8);
    p->y = p->y - data_ov003_0223bda4;
    t = (*n * 0x199a) >> 5;
    if (t > 0x199a) {
        t = 0x199a;
    }
    func_02031288((UnkStruct_0222bfe0 *) o, p, p, func_0200322c((Vec3 *) (o + 0x4c), (Vec3 *) (o + 0x40)), t, 0, 0xb);
    *n = *n + 1;
    if (*n >= 0x78) {
        *(u8 *) (o + 0x30) = 0;
        {
            Vec3 *q = (Vec3 *) (o + 0x4c);
            q->x = 0x1000;
            q->y = 0x1000;
            q->z = 0x1000;
        }
    }
}
