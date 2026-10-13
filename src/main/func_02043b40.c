/* func_02043b40 @ 0x02043b40, 0x19c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pt;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204f294(void *ctx, int x, int y);
extern int func_02042f20(void *g, void *a0, int kind, Pt *v, int p5, int p6, int p7, int p8, int p9, int p10);

extern void *data_021c80bc;
extern int data_021c7c48;

int func_02043b40(void *a0, Pt *p)
{
    int ret;
    unsigned int d;
    unsigned int c;
    unsigned int b;
    unsigned int a;
    void *ctx;
    Pt v3;
    unsigned int e;
    unsigned int t;
    unsigned int v;
    unsigned int v2;
    unsigned short *o;
    int kind;
    int x, z;
    int cx, cz;
    int hi;

    ctx = data_021c80bc;
    ret = -1;
    if (ctx == 0) {
        goto tail;
    }
    x = p->x;
    z = p->y;
    cx = x >> 4;
    cz = z >> 4;
    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (o == 0) {
        goto tail;
    }
    t = *o;
    kind = 0;
    if (t == 0xfff1) {
        ret = -1;
        goto done;
    }
    if ((t >= 0x21 && t <= 0x24) || t == 0x1f) {
        kind = 5;
        goto done;
    }
    hi = ((int) (t & 0xf000)) >> 12;
    if (hi == 1) {
        if (func_0204f294(ctx, p->x, p->y) == 0) {
            goto set3;
        }
    }
    d = 1;
    c = 1;
    b = 1;
    a = 0;
    v = *o;
    if (v <= 5) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 6 && v <= 0xb)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0xc && v <= 0x11)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
            d = 0;
        }
    }
    if (d != 0) {
        goto set3;
    }
    if (t == 0x1a) {
        goto set3;
    }
    if (t == 0x1d) {
        goto set3;
    }
    if (t == 0x1e) {
        goto set3;
    }
    hi = ((int) (v & 0xf000)) >> 12;
    if (hi == 3) {
        goto chk2;
    }
    if (hi == 4) {
    chk2:
        if (func_0204f294(ctx, p->x, p->y) == 0) {
            goto set3;
        }
    }
    e = 0;
    v2 = *o;
    if (v2 >= 0xa7 && v2 <= 0xc6) {
        e = 1;
    }
    if (e != 0) {
    set3:
        kind = 3;
        goto done;
    }
    if ((v2 >= 0x6e && v2 <= 0x73) || (v2 >= 0x74 && v2 <= 0x79) || (v2 >= 0x7a && v2 <= 0x7f) || (v2 >= 0x80 && v2 <= 0x87) ||
        (v2 >= 0x8a && v2 <= 0x8f) || (v2 >= 0x90 && v2 <= 0x95) || (v2 >= 0x96 && v2 <= 0x9b) || (v2 >= 0x9c && v2 <= 0xa3) ||
        v2 == 0xa5 || t == 0x88 || t == 0xa4) {
        kind = 5;
        goto done;
    }
    if (t == 0x20) {
        kind = 0x15;
    }
done:
    if (kind != 0) {
        v3.x = p->x;
        v3.y = p->y;
        ret = func_02042f20(&data_021c7c48, a0, kind, &v3, 0xfff1, t, 0, 0, 0, -1);
    }
tail:
    return ret;
}
