/* func_0207ec84 @ 0x0207ec84, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern int func_02095794(int a);
extern void func_0204f818(int *px, int *pz, void *q);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern unsigned char data_020e54a8;
extern void *data_021c80bc;

int func_0207ec84(void)
{
    void *q;
    unsigned int ok;
    void *obj;
    int x, z;
    int cx, cz;
    int h, g, f, e, d, c, b, a;
    unsigned int v;
    unsigned short *o;
    int count;
    int px, pz;

    q = (void *) func_02095794(4);
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        if (q != 0) {
            obj = data_021c80bc;
            if (obj != 0) {
                count = 0;
                px = 0;
                pz = 0;
                func_0204f818(&px, &pz, q);
                z = pz - 1;
                while (z <= pz + 1) {
                    x = px - 1;
                    while (x <= px + 1) {
                        cx = x >> 4;
                        cz = z >> 4;
                        o = func_0204f5e0(obj, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                        if (o != 0) {
                            h = 1;
                            g = 1;
                            f = 1;
                            e = 1;
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
                            if (d == 0) {
                                if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
                                      (v >= 0x9c && v <= 0xa3) || v == 0xa5)) {
                                    e = 0;
                                }
                            }
                            if (e == 0) {
                                if (v != 0x1a) {
                                    f = 0;
                                }
                            }
                            if (f == 0) {
                                if (v != 0xa4) {
                                    g = 0;
                                }
                            }
                            if (g == 0) {
                                if (v != 0x1d) {
                                    h = 0;
                                }
                            }
                            if (h != 0) {
                                count++;
                                if (count >= 2) {
                                    return 1;
                                }
                            }
                        }
                        x++;
                    }
                    z++;
                }
            }
        }
    }
    return 0;
}
