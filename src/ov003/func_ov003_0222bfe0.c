/* func_ov003_0222bfe0 @ 0x0222bfe0, 0x14c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

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
