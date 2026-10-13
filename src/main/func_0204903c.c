/* func_0204903c @ 0x0204903c, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

typedef struct {
    int w;
    int h;
} Size;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204a150(void *ctx, unsigned short *o, int x, int z);

void func_0204903c(int a0, void *ctx, Size *sz)
{
    int x, z;
    int cx, cz;
    int i, h, g, f, e, d, c, b, a;
    unsigned int t;
    unsigned short *o;

    z = 0;
    while (z < sz->h) {
        x = 0;
        if (sz->w > 0) {
            cz = z >> 4;
            for (; x < sz->w; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                if (o == 0) {
                    continue;
                }
                i = 1;
                h = 1;
                g = 1;
                f = 1;
                e = 1;
                d = 1;
                c = 1;
                b = 1;
                a = 0;
                t = *o;
                if (t >= 0x26 && t <= 0x2a) {
                    a = 1;
                }
                if (a == 0) {
                    if (t < 0x5d || t > 0x61) {
                        b = 0;
                    }
                }
                if (b == 0) {
                    if (t < 0x2f || t > 0x56) {
                        c = 0;
                    }
                }
                if (c == 0) {
                    if (t < 0x57 || t > 0x5b) {
                        d = 0;
                    }
                }
                if (d == 0) {
                    if (t < 0x66 || t > 0x68) {
                        e = 0;
                    }
                }
                if (e == 0) {
                    if (t != 0x69) {
                        f = 0;
                    }
                }
                if (f == 0) {
                    if (t < 0x6a || t > 0x6c) {
                        g = 0;
                    }
                }
                if (g == 0) {
                    if (t != 0x6d) {
                        h = 0;
                    }
                }
                if (h == 0) {
                    if (t < 0xc8 || t > 0xcf) {
                        i = 0;
                    }
                }
                if (i != 0) {
                    func_0204a150(ctx, o, x, z);
                }
            }
        }
        z++;
    }
}
