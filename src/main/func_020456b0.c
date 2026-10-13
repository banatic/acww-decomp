/* func_020456b0 @ 0x020456b0, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pos;

extern u8 data_020ca640[];
extern int data_020cb488[];

extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern int func_0204ee7c(int a, int x, int y);
extern int func_02045d80(Pos *p, int q);

int func_020456b0(void *unused, Pos *pos, int idx, int ctx)
{
    int i;
    int *base;
    int zero;
    int w;
    int *p;
    int v;
    int x, y;
    int xs, ys;
    int off;
    u16 *r;
    Pos tmp;

    off = idx * 32;
    base = (int *) ((char *) data_020cb488 + off);
    p = base;
    i = 0;
    w = 0;
    zero = 0;
    for (; i < 8; i++) {
        v = data_020ca640[*p];
        x = pos->x + ((v >> 4) - 8);
        y = pos->y + ((v & 0xf) - 8);
        xs = x >> 4;
        ys = y >> 4;
        r = func_0204f5e0(ctx, xs, ys, x - (xs << 4), y - (ys << 4), zero);
        if (r != 0 && *r == 0xfff1) {
            if (func_0204ee7c(ctx, x, y) != 0) {
                tmp.x = x;
                tmp.y = y;
                if (func_02045d80(&tmp, w) < 0) {
                    pos->x = x;
                    pos->y = y;
                    return 1;
                }
            }
        }
        p++;
    }
    v = data_020ca640[*base];
    pos->x = pos->x + ((v >> 4) - 8);
    pos->y = pos->y + ((v & 0xf) - 8);
    return 0;
}
