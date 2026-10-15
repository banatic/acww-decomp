/* func_02049638 @ 0x02049638, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern int data_020cac3c[][2];

extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204ba94(unsigned short *);

struct UnkStruct_02049638 {
    int w;
    int h;
};
struct Pair {
    int a;
    int b;
};

extern int func_020496cc(void *a, void *ctx, struct Pair *pa, struct Pair *pb);

void func_02049638(void *a, void *ctx, struct UnkStruct_02049638 *p)
{
    struct Pair pa;
    struct Pair pb;
    int *row;
    void *o;
    int k;
    int x;
    int z;
    int cx;
    int cz;
    int z0;
    int layer;

    k = 0;
    z0 = 0;
    layer = 0;
    for (; k < 3; k++) {
        z = z0;
        row = data_020cac3c[k];
        for (; z < p->h; z++) {
            x = row[z & 1];
            if (x < p->w) {
                cz = z >> 4;
                for (; x < p->w; x += 4) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o == 0) {
                        continue;
                    }
                    if (func_0204ba94(o) == 0) {
                        continue;
                    }
                    pb.a = x;
                    pb.b = z;
                    pa.a = p->w;
                    pa.b = p->h;
                    func_020496cc(a, ctx, &pa, &pb);
                }
            }
        }
    }
}
