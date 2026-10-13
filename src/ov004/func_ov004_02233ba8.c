/* func_ov004_02233ba8 @ 0x02233ba8, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern void *data_021c80bc;
extern char *data_020ccf94;
extern void *func_020961a8(int);
extern int func_02073d90(void *);
extern int func_ov004_0223356c(int, int, Vec3 *, Vec3 *, unsigned char);

int func_ov004_02233ba8(u16 *self, Vec3 *b)
{
    Vec3 va, vb;
    int r;
    void *g = data_021c80bc;
    void *p = func_020961a8(4);
    r = 0;
    if (g != 0 && p != 0) {
        char *c = data_020ccf94;
        int v;
        Vec3 *q;
        if (func_02073d90(c) != 0) {
            v = *(int *) (c + 0x64);
        } else {
            v = 0;
        }
        q = (Vec3 *) ((char *) p + 0x5c);
        va.x = q->x;
        va.y = q->y;
        va.z = q->z;
        vb.x = b->x;
        vb.y = b->y;
        vb.z = b->z;
        if (func_ov004_0223356c(v, *self, &va, &vb, 0) != 0) {
            r = 1;
        } else {
            r = 0;
        }
    }
    return r;
}
