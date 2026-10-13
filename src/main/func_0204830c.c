/* func_0204830c @ 0x0204830c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x18];
    u16 unk_18;
} Cnt;

extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204a25c(int a, int b, int c, int d, int e);
extern int func_020644cc(int);
extern u16 data_020ca59c[];

int func_0204830c(int p0, int p1, Cnt *cnt, int k, int x, int y)
{
    int start;
    int z6;
    int zok;
    int count;
    int inner;
    int outer;
    int t;
    int ok;
    unsigned int v;
    u16 *r;
    int tv;
    int out1;
    int out2;

    t = cnt->unk_18;
    count = func_020644cc(t);
    cnt->unk_18 = t - 1;
    start = 0;
    zok = 0;
    z6 = 0;
    for (outer = 0; outer < 0x10; outer++) {
        for (inner = start; inner < 0x10; inner++) {
            r = func_0204f5e0(p1, x + 1, y + 1, inner, outer, z6);
            if (r == 0) {
                continue;
            }
            ok = zok;
            v = *r;
            if (v >= 0xe3 && v <= 0xe7) {
                ok = 1;
            }
            if (ok == 0) {
                continue;
            }
            count = count - 1;
            if (count >= 0) {
                continue;
            }
            func_0204f800(&out1, &out2, x + 1, y + 1, inner, outer);
            tv = data_020ca59c[k];
            func_0204a25c(p1, out1, out2, (u16) (tv + (int) (v - 0xe3) % 5), 0);
            return 1;
        }
    }
    return 0;
}
