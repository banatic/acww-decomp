/* func_020488e4 @ 0x020488e4, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern int func_02048ec8(int a, int b, int c);
extern int func_02048d2c(int a, int b, int c, Pt *d, int e, int f);
extern int func_020644cc(int);
extern u8 data_020cab28[];
extern u16 data_020cabc4[];

void func_020488e4(int p0, int p1, Pt *base, int cnt)
{
    Pt list[17];
    int n;
    int idx;
    int x;
    int y;
    int x4;
    int y4;
    int count;
    int i;
    u8 d;
    u16 *r;
    Pt *e;

    e = list;
    do {
        e->x = 0;
        e->y = 0;
        e++;
    } while (e != list + 17);
    n = 0;
    for (idx = 0; idx < 0x11; idx++) {
        d = data_020cab28[idx];
        x = base->x + ((d >> 4) - 8);
        y = base->y + ((d & 0xf) - 8);
        x4 = x >> 4;
        y4 = y >> 4;
        r = func_0204f5e0(p1, x4, y4, x - (x4 << 4), y - (y4 << 4), 0);
        if (r != 0 && *r == 0xfff1) {
            if (func_02048ec8(p1, x, y) != 0) {
                list[n].x = x;
                list[n].y = y;
                n++;
            }
        }
    }
    count = cnt << 1;
    while (n > 0) {
        i = func_02048d2c(p0, p1, n, list, data_020cabc4[func_020644cc(0xc)], 0);
        count = count - 1;
        if (count <= 0) {
            break;
        }
        while (i < 0x10) {
            list[i].x = list[i + 1].x;
            list[i].y = list[i + 1].y;
            i++;
        }
        n = n - 1;
    }
}
