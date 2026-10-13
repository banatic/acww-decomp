/* func_0205ac84 @ 0x0205ac84, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *o);
extern int func_0204bc64(void *o);
extern int func_02053c34(int n);
extern int func_0206226c(int n);

struct Rect {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
};

int func_0205ac84(struct Rect *p, void *ctx)
{
    unsigned char layer;
    int total;
    int z;
    int x;
    int cx;
    int cz;
    void *o;

    total = 0;
    for (layer = 0; layer < 2; layer++) {
        for (z = p->z0; z <= p->z1; z++) {
            x = p->unk_00;
            if (x <= p->x1) {
                cz = z >> 4;
                for (; x <= p->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o != 0 && func_0204bcdc(o) != 0) {
                        total += func_0206226c(func_02053c34(func_0204bc64(o)));
                    }
                }
            }
        }
    }
    return total;
}
