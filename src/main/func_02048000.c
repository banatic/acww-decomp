/* func_02048000 @ 0x02048000, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

typedef struct {
    int w;
    int h;
} Size;

typedef struct {
    int unk_00;
    Size sz;
} UnkStruct_02048000;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204a25c(void *ctx, int x, int z, int k, int m);

void func_02048000(int unused, UnkStruct_02048000 *ctx, int n)
{
    Size *s;
    int limitX, limitZ;
    int x, z;
    int cx, cz;
    unsigned short t;
    unsigned int ok;
    unsigned short *o;

    s = &ctx->sz;
    limitX = s->w << 4;
    limitZ = s->h << 4;

    for (z = 0; z < limitZ; z++) {
        x = 0;
        if (limitX > 0) {
            cz = z >> 4;
            for (; x < limitX; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                if (o == 0) {
                    continue;
                }
                ok = 0;
                t = *o;
                if (t >= 0xd4 && t <= 0xda) {
                    ok = 1;
                }
                if (ok != 0) {
                    func_0204a25c(ctx, x, z, 0xe2, 0);
                    continue;
                }
                if (t >= 0xdb && t <= 0xe1) {
                    if (n > 1) {
                        func_0204a25c(ctx, x, z, 0xe2, 0);
                    } else if (t != 0xe1) {
                        func_0204a25c(ctx, x, z, (unsigned short) (t - 6), 0);
                    } else {
                        func_0204a25c(ctx, x, z, (unsigned short) (t - 7), 0);
                    }
                } else if (t == 0xe2) {
                    func_0204a25c(ctx, x, z, 0xfff1, 0);
                } else if (t >= 0x154a && t <= 0x1553) {
                    func_0204a25c(ctx, x, z, 0xfff1, 0);
                }
            }
        }
    }
}
