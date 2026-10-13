/* func_02049bc4 @ 0x02049bc4, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02049ec4(unsigned short *o);
extern int func_02049d04(unsigned short *a, unsigned short *b);

struct Vec {
    int x;
    int z;
};

extern int func_020498b0(void *ctx, struct Vec *a, struct Vec *b, int k);

int func_02049bc4(void *ctx, struct Vec *v1, struct Vec *v2, struct Vec *v3)
{
    struct Vec a;
    struct Vec b;
    struct Vec c;
    struct Vec d;
    unsigned short *o1;
    unsigned short *o2;
    int ret;
    int t;
    int k;
    int ok;
    int x;
    int z;
    int cx;
    int cz;

    ret = 0;
    x = v1->x;
    z = v1->z;
    cx = x >> 4;
    cz = z >> 4;
    o1 = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), ret);
    if (o1 == 0) {
        goto end;
    }
    ok = 0;
    if (*o1 <= 0x19) {
        ok = 1;
    }
    if (ok == 0) {
        goto end;
    }
    x = v2->x;
    z = v2->z;
    cx = x >> 4;
    cz = z >> 4;
    o2 = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    t = func_02049ec4(o2);
    if (t != func_02049ec4(o1)) {
        goto end;
    }
    k = func_02049d04(o2, o1);
    if (k == 0xfff1) {
        goto end;
    }
    b.x = v2->x;
    b.z = v2->z;
    a.x = v3->x;
    a.z = v3->z;
    if (func_020498b0(ctx, &a, &b, k) != 0) {
        ret = 1;
        goto end;
    }
    d.x = v1->x;
    d.z = v1->z;
    c.x = v3->x;
    c.z = v3->z;
    ret = func_020498b0(ctx, &c, &d, k);
end:
    return ret;
}
