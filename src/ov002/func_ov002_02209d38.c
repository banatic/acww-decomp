/* func_ov002_02209d38 @ 0x02209d38, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Anim {
    int unk_00;
    int x;
    int y;
    int dx;
    int dy;
    u8 steps;
    u8 mode;
};

void func_ov002_02209d38(struct Anim *p, int x, int y, int steps)
{
    p->mode = 2;
    p->dx = ((x << 4) - p->x) / steps;
    p->dy = ((y << 4) - p->y) / steps;
    p->steps = steps;
}
