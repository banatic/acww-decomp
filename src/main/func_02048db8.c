/* func_02048db8 @ 0x02048db8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 unk_00;
} Entry;
typedef struct {
    int x;
    int y;
} Pair;

extern Entry *func_0204f5e0(int ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f800(int *out0, int *out1, int a, int b, int c, int d);

int func_02048db8(int p0, Pair *out, int ctx, int cx, volatile int cz, int (*cb)(int, int, int))
{
    int czl;
    int count;
    int x, z;
    Entry *e;
    int out0, out1;

    count = 0;
    z = 0;
    czl = cz;
    for (; z < 16; z++) {
        for (x = 0; x < 16; x++) {
            e = func_0204f5e0(ctx, cx, czl, x, z, 0);
            if (e == 0) {
                continue;
            }
            if (e->unk_00 != 0xfff1) {
                continue;
            }
            func_0204f800(&out0, &out1, cx, czl, x, z);
            if (cb(ctx, out0, out1) != 0) {
                out->x = out0;
                out->y = out1;
                out++;
                count++;
            }
        }
    }
    return count;
}
