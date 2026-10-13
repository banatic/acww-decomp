/* func_020496f8 @ 0x020496f8, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204ba94(void *o);

struct UnkStruct_020496f8 {
    int w;
    int h;
};
struct Pair {
    int a;
    int b;
};

extern void func_020497e4(void *a, void *ctx, unsigned short *o, struct Pair *q, int x, int z);
extern void func_020497b0(void *a, void *ctx, unsigned short *o, struct Pair *q, int x, int z);
extern void func_02049818(void *a, void *ctx, unsigned short *o, struct Pair *q, int x, int z);

void func_020496f8(void *a, void *ctx, struct UnkStruct_020496f8 *p)
{
    struct Pair qa;
    struct Pair qb;
    struct Pair qc;
    unsigned short *o;
    int z;
    int x;
    int cx;
    int cz;
    int x0;
    int layer;

    z = 0;
    layer = 0;
    x0 = 0;
    for (; z < p->h; z++) {
        x = x0;
        if (p->w > 0) {
            cz = z >> 4;
            for (; x < p->w; x++) {
                cx = x >> 4;
                o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                if (o == 0) {
                    continue;
                }
                if (func_0204ba94(o) == 0) {
                    continue;
                }
                switch (*o) {
                    case 0x5d:
                        qa.a = p->w;
                        qa.b = p->h;
                        func_020497e4(a, ctx, o, &qa, x, z);
                        break;
                    case 0xc8:
                        qb.a = p->w;
                        qb.b = p->h;
                        func_020497b0(a, ctx, o, &qb, x, z);
                        break;
                    default:
                        qc.a = p->w;
                        qc.b = p->h;
                        func_02049818(a, ctx, o, &qc, x, z);
                        break;
                }
            }
        }
    }
}
