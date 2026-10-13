/* func_02087950 @ 0x02087950, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

extern void MI_CpuFill8(void *dst, int val, int n);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02088024(int x, int y, int c);
extern void func_0204f794(int a, int x, int y);
extern int func_020644cc(int);

int func_02087950(int p0, int p1, Pt *p2, int p3)
{
    int bx;
    int by;
    int startx;
    int count;
    int xi;
    int yi;
    int k;
    u16 *m;
    u16 *m2;
    int xj;
    int yj;
    u16 mask[16];

    count = 0;
    bx = 0;
    by = 0;
    MI_CpuFill8(mask, 0, 0x20);
    func_0204f800(&bx, &by, p2->x, p2->y, 0, 0);
    yi = 0;
    startx = 0;
    for (yi = 0; yi < 0x10; yi++) {
        xi = startx;
        m = &mask[yi];
        for (; xi < 0x10; xi++) {
            if (func_02088024(bx + xi, by + yi, p3) != 0) {
                *m = *m | (1 << xi);
                count++;
            }
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        for (yj = 0; yj < 0x10; yj++) {
            xj = 0;
            m2 = &mask[yj];
            for (; xj < 0x10; xj++) {
                if (((*m2 >> xj) & 1) != 0) {
                    if (k == 0) {
                        func_0204f794(p1, bx + xj, by + yj);
                        return 1;
                    }
                    k--;
                }
            }
        }
    }
    return 0;
}
