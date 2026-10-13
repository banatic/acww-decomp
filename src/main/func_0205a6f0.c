/* func_0205a6f0 @ 0x0205a6f0, 0xe2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *o);
extern int func_0204bc64(void *o);
extern int func_0204bc7c(void *o);
extern int func_0204bd08(void *o);
extern int func_02053b2c(int a);

struct Rect {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
};

int func_0205a6f0(struct Rect *p, void *ctx, unsigned char *pa, unsigned char *pb)
{
    void *o;
    unsigned char layer;
    int total;
    int z;
    int x;
    int cx;
    int cz;
    int d;

    total = 0;
    layer = 0;
    for (; layer < 2; layer++) {
        for (z = p->z0; z <= p->z1; z++) {
            x = p->unk_00;
            if (x <= p->x1) {
                cz = z >> 4;
                for (; x <= p->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o == 0) {
                        continue;
                    }
                    if (func_0204bcdc(o) != 0) {
                        if (func_02053b2c(func_0204bc64(o)) == 0) {
                            continue;
                        }
                        d = func_0204bc7c(o);
                        if (x == p->unk_00 && d == 3) {
                            *pa = 1;
                            total += 0x64;
                        }
                        if (x == p->x1 && d == 1) {
                            *pa = 1;
                            total += 0x64;
                        }
                        if (z == p->z0 && d == 2) {
                            *pa = 1;
                            total += 0x64;
                        }
                        if (z == p->z1 && d == 0) {
                            *pa = 1;
                            total += 0x64;
                        }
                    } else {
                        if (func_0204bd08(o) != 0) {
                            *pb = 1;
                            total += 1;
                        }
                    }
                }
            }
        }
    }
    return total;
}
