/* func_ov004_02233a00 @ 0x02233a00, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} UnkStruct_02233a00;
extern void func_ov004_02233918(void *, UnkStruct_02233a00 *, Vec3 *, Vec3 *, u16);

void func_ov004_02233a00(char *self, int a, UnkStruct_02233a00 *b, Vec3 *c, Vec3 *d, int e, u16 f7, int a8, short a9, u8 a10)
{
    char *q;
    UnkStruct_02233a00 bb;
    Vec3 cc, dd;
    *(int *) self = a;
    *(int *) (self + 4) = 1;
    *(int *) (self + 0xc) = e;
    *(int *) (self + 0x10) = b->a;
    *(int *) (self + 0x14) = b->b;
    *(int *) (self + 0x18) = d->x;
    *(int *) (self + 0x1c) = d->y;
    *(int *) (self + 0x20) = d->z;
    *(short *) (self + 0x48) = a9;
    *(short *) (self + 0x4a) = 0;
    *(u8 *) (self + 0x8e) = 1;
    *(u8 *) (self + 0x8f) = 1;
    q = self;
    q += 0x90;
    *q = (char) a10;
    *(u8 *) (self + 0x8d) = 0;
    *(u8 *) (self + 0x8c) = 0;
    if (e == 0) {
        cc.x = c->x;
        cc.y = c->y;
        cc.z = c->z;
        dd.x = d->x;
        dd.y = d->y;
        dd.z = d->z;
        bb.a = b->a;
        bb.b = b->b;
        func_ov004_02233918(self, &bb, &cc, &dd, f7);
    }
}
