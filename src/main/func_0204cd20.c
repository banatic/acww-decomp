/* func_0204cd20 @ 0x0204cd20, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern unsigned short data_020cb758[];

extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f538(void *ctx, unsigned short *h, int x, int z, int m);
extern void func_0204f31c(void *ctx, int x, int z);

struct Vec2 {
    int x;
    int z;
};
struct UnkStruct_0204cd20_2 {
    int unk_00;
    struct Vec2 size;
};
struct UnkStruct_0204cd20 {
    int unk_00;
    int unk_04;
};

void func_0204cd20(struct UnkStruct_0204cd20 *a)
{
    int layer;
    int x;
    unsigned short hh;
    unsigned short *o;
    int z;
    int m;
    int x0;
    struct UnkStruct_0204cd20_2 *ctx;
    struct Vec2 *sz;
    int h;
    int ok;
    unsigned short id;
    int cx;
    int w;
    int ok0;
    int cz;

    ctx = (struct UnkStruct_0204cd20_2 *) func_0204e414();
    if (ctx == 0) {
        return;
    }
    sz = &ctx->size;
    w = sz->x << 4;
    h = sz->z << 4;
    z = 0;
    id = data_020cb758[a->unk_04];
    ok0 = 0;
    m = 0;
    layer = 0;
    x0 = 0;
    for (; z < h; z++) {
        x = x0;
        if (w > 0) {
            cz = z >> 4;
            for (; x < w; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                if (o != 0) {
                    ok = ok0;
                    if (*o >= 0x2f && *o <= 0x56) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        hh = id;
                        func_0204f538(ctx, &hh, x, z, m);
                        func_0204f31c(ctx, x, z);
                    }
                }
            }
        }
    }
}
