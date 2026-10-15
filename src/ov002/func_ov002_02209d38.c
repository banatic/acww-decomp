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

int func_ov002_02209d38(struct Anim *p, int x, int y, int steps)
{
    int result;
    p->mode = 2;
    p->dx = ((x << 4) - p->x) / steps;
    result = ((y << 4) - p->y) / steps;
    p->dy = result;
    p->steps = steps;
    return result;
}
