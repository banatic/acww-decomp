/* func_020481a0 @ 0x020481a0, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204a200(int a0, void *ctx, int cx, int cz, int dx, int dz, int id, int f);
struct UnkStruct_020481a0 {
    int pad_00;
    int w;
    int h;
};
void func_020481a0(int a0)
{
    int cx;
    int xmax;
    int cz;
    int ymax;
    volatile int start;
    int dx;
    void *ctx;
    volatile int something;
    unsigned short *p;
    int ok;
    int dz;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    xmax = ((struct UnkStruct_020481a0 *) ctx)->w - 2;
    ymax = ((struct UnkStruct_020481a0 *) ctx)->h - 2;
    start = 1;
    something = 1;
    for (cz = 1; cz <= ymax; cz++) {
        for (cx = start; cx <= xmax; cx++) {
            for (dz = 0; dz < 16; dz++) {
                for (dx = 0; dx < 16; dx++) {
                    p = func_0204f5e0(ctx, cx, cz, dx, dz, 0);
                    if (p != 0) {
                        ok = 0;
                        if (*p >= 0xfc && *p <= 0xfd) {
                            ok = something;
                        }
                        if (ok != 0) {
                            func_0204a200(a0, ctx, cx, cz, dx, dz, 0xfff1, 0);
                        }
                    }
                }
            }
        }
    }
}
