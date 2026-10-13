/* func_ov002_02209d8c @ 0x02209d8c, 0x8c bytes, Thumb, module ov002
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

int func_ov002_02209d8c(struct Anim *p)
{
    if (p->mode != 2 && p->mode != 3) {
        return 1;
    }
    if (p->steps != 0) {
        p->steps = p->steps - 1;
        switch (p->mode) {
            case 2:
                p->x += p->dx;
                p->y += p->dy;
                break;
            case 3:
                p->x += p->dx;
                p->y += p->dy;
                if (p->steps > 1) {
                    p->dx = p->dx >> 1;
                    p->dy = p->dy >> 1;
                }
                break;
        }
        while (p->x < 0) {
            p->x += 0x1000;
        }
        while (p->x > 0x1000) {
            p->x -= 0x1000;
        }
    }
    if (p->steps == 0) {
        return 1;
    }
    return 0;
}
