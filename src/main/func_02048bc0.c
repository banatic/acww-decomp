/* func_02048bc0 @ 0x02048bc0, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204a25c(int a, int b, int c, int d, int e);
extern int func_020644cc(int);

int func_02048bc0(int p0, int p1, int p2, int p3, int p4)
{
    int result;
    int x;
    int y;
    Pt list[256];
    u16 kinds[256];
    Pt *e;
    int inner;
    int count;
    int outer;
    int k;
    u16 v;
    u16 *p;

    e = list;
    do {
        e->x = 0;
        e->y = 0;
        e++;
    } while (e != list + 256);
    count = 0;
    result = 0;
    for (outer = 0; outer < 0x10; outer++) {
        for (inner = 0; inner < 0x10; inner++) {
            p = func_0204f5e0(p1, p2, p3, inner, outer, 0);
            if (p == 0) {
                continue;
            }
            func_0204f800(&x, &y, p2, p3, inner, outer);
            v = *p;
            switch (v) {
                case 0x2a:
                    list[count].x = x;
                    list[count].y = y;
                    kinds[count] = 0x66;
                    count++;
                    break;
                case 0x61:
                    list[count].x = x;
                    list[count].y = y;
                    kinds[count] = 0x6a;
                    count++;
                    break;
            }
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        func_0204a25c(p1, list[k].x, list[k].y, (u16) (p4 + kinds[k]), 0);
        result = 1;
    }
    return result;
}
