/* func_0205a7d4 @ 0x0205a7d4, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *o);
extern int func_02053b6c(void *o);

struct Rect {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
};

int func_0205a7d4(struct Rect *p, void *ctx, int *pOut)
{
    unsigned char counts[5];
    void *o;
    unsigned char layer;
    unsigned char *q;
    int z;
    int x;
    int cx;
    int cz;
    unsigned int i;
    int total;
    int k;

    MI_CpuFill8(counts, 0, 5);
    layer = 0;
    for (; layer < 2; layer++) {
        for (z = p->z0; z <= p->z1; z++) {
            x = p->unk_00;
            if (x <= p->x1) {
                cz = z >> 4;
                for (; x <= p->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o != 0 && func_0204bcdc(o) != 0) {
                        k = func_02053b6c(o);
                        counts[k] = counts[k] + 1;
                    }
                }
            }
        }
    }
    total = 0;
    for (i = 0; i < 5; i++) {
        if (i != 4) {
            q = &counts[i];
            if (counts[i] >= 8) {
                *pOut = i;
                total = total + 0x190 * *q;
            }
        }
    }
    return total;
}
