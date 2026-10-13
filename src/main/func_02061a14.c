/* func_02061a14 @ 0x02061a14, 0xae bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_02061ac4(unsigned short *dst, unsigned short *o);
extern int func_0204bcdc(unsigned short *o);
extern int func_0204bc64(unsigned short *o);
extern void func_0204f538(void *ctx, unsigned short *h, int x, int z, int m);

struct UnkStruct_02061a14 {
    char pad_00[0xc];
    int w;
    int h;
};

void func_02061a14(struct UnkStruct_02061a14 *ctx)
{
    unsigned short tmp;
    unsigned short *o;
    int z;
    int x;
    int cx;
    int cz;
    int v;
    int a;
    int x0;
    int layer;
    int zA;
    int zB;
    int m;

    if (ctx == 0) {
        return;
    }
    z = 0;
    zA = 0;
    zB = 0;
    m = 0;
    layer = 0;
    x0 = 0;
    for (; z < ctx->h; z++) {
        x = x0;
        if (ctx->w > 0) {
            cz = z >> 4;
            for (; x < ctx->w; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                if (o == 0) {
                    continue;
                }
                func_02061ac4(&tmp, o);
                if (func_0204bcdc(o) != 0) {
                    a = func_0204bc64(o);
                    if (a == func_0204bc64(&tmp)) {
                        v = 1;
                    } else {
                        v = zA;
                    }
                } else {
                    if (*o == tmp) {
                        v = 1;
                    } else {
                        v = zB;
                    }
                }
                if (v != 0) {
                    continue;
                }
                func_0204f538(ctx, &tmp, x, z, m);
            }
        }
    }
}
