/* func_ov004_0220d904 @ 0x0220d904, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern int func_ov004_0220d94c(char *self);
int func_ov004_0220d904(char *self, u16 *b, Vec3 *c)
{
    int r;
    if (func_ov004_0220d94c(self) == 0) {
        *(u16 *) (self + 2) = *b;
        *(int *) (self + 4) = c->x;
        *(int *) (self + 8) = c->y;
        *(int *) (self + 0xc) = c->z;
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
