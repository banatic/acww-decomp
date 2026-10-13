/* func_ov068_02271494 @ 0x02271494, 0x10c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, void *v);
extern unsigned short func_0204bbd4(unsigned int i);
extern void *func_020b3b50(unsigned short *r);
extern unsigned int func_020b3f44(void *h);
extern void *func_ov003_02220174(unsigned short r);
extern int func_020b3e8c(void *h, int *a, int *b, unsigned int j);
extern int func_ov009_02262fa4(void *o);
extern int func_ov009_02262fc0(void *o);
extern int func_ov009_02262fb4(void *o);
extern int func_020ea990(void *a, void *b);
extern void func_0204f794(int *out, int a, int b);

typedef struct {
    int x, y, z;
} Vec3;

int func_ov068_02271494(char *a, Vec3 *out)
{
    int best;
    unsigned int i;
    unsigned int j;
    int bx, bz;
    void *h;
    unsigned int n;
    void *o;
    int px, pz;
    int c0, j0, y0;
    unsigned short room;
    int gx, gz;
    int cx, cz;
    Vec3 c;
    Vec3 va;
    struct {
        int x, y, z, p1, p2;
    } vb;
    int d;

    bx = 0;
    best = -1;
    gx = 0;
    gz = 0;
    bz = 0;
    c.x = -1;
    c.y = 0;
    c.z = -1;
    va.x = 0;
    va.y = 0;
    va.z = 0;
    func_0204f818(&gx, &gz, a + 0x204);
    va.x = gx;
    i = 0;
    va.y = 0;
    va.z = gz;
    j0 = 0;
    y0 = 0;
    c0 = 0;
    for (; i < 0x22; i++) {
        room = func_0204bbd4(i);
        h = func_020b3b50(&room);
        if (h == 0) {
            continue;
        }
        n = func_020b3f44(h);
        cx = c0;
        cz = c0;
        if (n == 0) {
            continue;
        }
        o = func_ov003_02220174(room);
        if (o == 0) {
            continue;
        }
        for (j = j0; j < n; j++) {
            if (func_020b3e8c(h, &cx, &cz, j) == 0) {
                continue;
            }
            if (func_ov009_02262fa4(o) != 1) {
                continue;
            }
            px = cx + func_ov009_02262fc0(o);
            pz = cz + func_ov009_02262fb4(o);
            vb.x = px;
            vb.y = y0;
            vb.z = pz;
            d = func_020ea990(&va, &vb);
            if ((va.z <= pz && best < 0) || d < best) {
                best = d;
                bx = px;
                bz = pz;
            }
        }
    }
    if (best >= 0) {
        func_0204f794(&c.x, bx, bz);
        out->x = bx;
        out->z = bz;
    }
    return best;
}
