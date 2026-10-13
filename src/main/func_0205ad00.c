/* func_0205ad00 @ 0x0205ad00, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern unsigned int data_021c997c[];
extern unsigned int data_021c9a7c[];

extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *o);
extern int func_0204bc64(void *o);
extern int func_020539b0(int a);
extern int func_02053c88(int a);

struct Rect {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
};

void func_0205ad00(struct Rect *p, void *ctx)
{
    unsigned char layer;
    void *o;
    int z;
    int x;
    int cx;
    int cz;
    int a;
    int b;
    int c;
    int mask;
    int zero;
    unsigned int tmp;

    layer = 0;
    zero = 0;
    for (; layer < 2; layer++) {
        for (z = p->z0; z <= p->z1; z++) {
            x = p->unk_00;
            if (x <= p->x1) {
                cz = z >> 4;
                for (; x <= p->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o != 0 && func_0204bcdc(o) != 0) {
                        a = func_0204bc64(o);
                        b = func_020539b0(a);
                        c = func_02053c88(a);
                        mask = zero;
                        if (b == 1) {
                            mask = 1;
                        } else if (b == 2) {
                            mask = 2;
                        } else if (b == 3) {
                            mask = 4;
                        } else if (b == 4) {
                            mask = 8;
                        }
                        tmp = mask;
                        tmp |= data_021c997c[c];
                        data_021c997c[c] = tmp;
                        data_021c9a7c[10] |= mask;
                    }
                }
            }
        }
    }
}
