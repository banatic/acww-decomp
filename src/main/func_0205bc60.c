/* func_0205bc60 @ 0x0205bc60, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

typedef struct {
    short x, y;
} Pt;
typedef struct {
    int unk_00, w1;
} It;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_02052e3c(It *it, void *src);
extern unsigned int func_02052e20(It *it);
extern Pt *func_02052dc0(It *it, unsigned int i);
extern void func_02052e38(It *it);
extern int func_02053cf0(int t);
extern int func_02053cbc(int t);

int func_0205bc60(int a0, void *ctx, unsigned int xmin, unsigned int xmax, volatile unsigned int zmin,
                  volatile unsigned int zmax, volatile int key)
{
    unsigned int count;
    unsigned char layer;
    int z, x;
    int cx;
    void *o;
    int h;
    unsigned int n, i;
    int ok;
    int px, pz;
    unsigned int z0, z1;
    int cz;
    It it;

    count = 0;
    layer = 0;
    z0 = zmin;
    z1 = zmax;
    do {
        for (z = z0; z <= z1; z++) {
            x = xmin;
            if (x <= xmax) {
                cz = z >> 4;
                for (; x <= xmax; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o == 0) {
                        continue;
                    }
                    if (func_0204bcdc(o) == 0) {
                        continue;
                    }
                    h = func_0204bc64(o);
                    func_02052e3c(&it, o);
                    n = func_02052e20(&it);
                    ok = 1;
                    for (i = 0; i < n; i++) {
                        px = x + func_02052dc0(&it, i)->x;
                        pz = z + func_02052dc0(&it, i)->y;
                        if (px < (int) xmin || px > (int) xmax || pz < (int) zmin || pz > (int) zmax) {
                            ok = 0;
                            break;
                        }
                    }
                    if (ok != 0) {
                        if (key == func_02053cf0(h)) {
                            count++;
                        }
                        if (key == func_02053cbc(h)) {
                            count++;
                        }
                    }
                    func_02052e38(&it);
                }
            }
        }
        layer++;
    } while (layer < 2);
    if (count < 0x100) {
        return (unsigned char) count;
    }
    return 0xff;
}
