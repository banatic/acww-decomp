/* func_0204cc98 @ 0x0204cc98, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204f538(void *ctx, unsigned short *h, int x, int z, int m);

struct Vec2 {
    int x;
    int z;
};
struct UnkStruct_0204cc98 {
    int unk_00;
    struct Vec2 size;
};

void func_0204cc98(void)
{
    struct UnkStruct_0204cc98 *ctx;
    unsigned short *o;
    unsigned short id2;
    int w;
    int h;
    int x;
    int z;
    int cx;
    int cz;
    int ok;
    struct Vec2 *sz;

    ctx = (struct UnkStruct_0204cc98 *) func_0204e414();
    if (ctx == 0) {
        return;
    }
    sz = &ctx->size;
    w = sz->x << 4;
    h = sz->z << 4;
    for (z = 0x30; z < h; z++) {
        x = 0;
        if (w > 0) {
            cz = z >> 4;
            for (; x < w; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                if (o != 0) {
                    ok = 0;
                    if (*o >= 0x5d && *o <= 0x61) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        id2 = 0x2a;
                        func_0204f538(ctx, &id2, x, z, 0);
                    }
                }
            }
        }
    }
}
