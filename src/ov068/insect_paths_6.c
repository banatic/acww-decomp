/* insect_paths_6: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02271494 @ 0x02271494, 0x10c bytes, Thumb
 * func_ov068_02271398 @ 0x02271398, 0xfc bytes, Thumb
 * func_ov068_02271358 @ 0x02271358, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

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
extern void func_ov003_02234cc4(u8 *self);
extern int func_ov003_02234d70(u8 *self);
extern void func_ov003_022353a4(u8 *self, int a, int b);
extern int func_ov068_022701b0(u8 *self, s16 *buf);
extern void func_ov068_0226fea4(u8 *self, s16 *buf, int c, int d, int e, int f);
extern int FX_Div(int a, int b);
extern int func_020644cc(int a);
extern void func_ov003_02234dac(u8 *self, int f232, int c, int d);
extern int func_ov003_02232414(void *);

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

void func_ov068_02271398(u8 *self)
{
    s16 buf;
    s16 f232;

    buf = *(s16 *) (self + 0x23a);
    f232 = *(s16 *) (self + 0x232);

    func_ov003_02234cc4(self);

    if (func_ov003_02234d70(self) == 2) {
        self[0x24a] = 0;
    }

    func_ov003_022353a4(self, 0, 1);

    if (self[0x24a] == 0) {
        if (func_ov068_022701b0(self, &buf) == 0) {
            if (*(s8 *) (self + 0x24d) == 0xa) {
                *(s16 *) (self + 0x242) = 0;
                self[0x251] = 9;
                return;
            }
        }
    }

    func_ov068_0226fea4(self, &buf, 0xaaa, 0x1e, 0x46, ((int) self[0x257]) << 12);

    if (*(s8 *) (self + 0x24d) == 0xa) {
        int r;
        int r2;

        r = FX_Div(0x12000, 0x10000);
        r2 = func_020644cc(8);
        func_ov003_02234dac(self, f232, r, (r2 + 0xa) << 12);
        *(s16 *) (self + 0x232) = f232 + 0xaaa;
    } else {
        int r2;

        r2 = func_020644cc(8);
        func_ov003_02234dac(self, f232, 0x19a, (r2 + 0x12) << 12);
        *(s16 *) (self + 0x232) = f232 + 0x1554;
    }
}

void func_ov068_02271358(void *p)
{
    short s;
    s = *(short *) ((char *) p + 0x232);
    if (func_ov003_02232414(p)) {
        if (s <= 0) {
            *(char *) ((char *) p + 0x251) = 9;
            *(short *) ((char *) p + 0x242) = 0;
        } else {
            *(short *) ((char *) p + 0x232) = s - 1;
        }
    }
}
