/* func_020498b0 @ 0x020498b0, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    volatile int x;
    volatile int y;
} Pt;

extern u8 data_020ca5d4[];
extern int func_020644cc(int);
extern int func_02049ca0(void *a, Pt *c, Pt *b, Pt *l, int e);

int func_020498b0(void *a0, Pt *lim, Pt *base, int a3)
{
    Pt c, b, l;
    int ok = 0;
    int idx = func_020644cc(8);
    int i;
    for (i = 0; i < 8; i++) {
        u8 d = data_020ca5d4[idx];
        int x = base->x - ((d >> 4) - 8);
        int y = base->y - ((d & 0xf) - 8);
        if (x >= 0 && x < lim->x && y >= 0 && y < lim->y) {
            l.x = lim->x;
            l.y = lim->y;
            b.x = base->x;
            b.y = base->y;
            c.x = x;
            c.y = y;
            if (func_02049ca0(a0, &c, &b, &l, a3)) {
                ok = 1;
                break;
            }
        }
        idx = (idx + 1) % 8;
    }
    return ok;
}
