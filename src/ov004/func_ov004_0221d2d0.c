/* func_ov004_0221d2d0 @ 0x0221d2d0, 0x198 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
extern int data_020ca0e4, data_020ca0e8;
extern unsigned data_ov004_02257a08;
extern Vec data_ov004_02257a94[6];
extern u8 data_ov004_02257a24[6][12];
extern void *data_ov004_02257a18;
extern int func_0202e364(void *), func_ov004_0223c5a4(Vec *), func_ov004_0221d068(void *);
extern void __register_global_object(void *, void (*)(void *), void *), func_020012dc(void *),
    func_01ffd070(Vec *, Vec *, Vec *);
extern void func_0201c280(void *, void *), func_ov004_0221cd48(void *, void *), func_ov004_0221c844(void *, int),
    func_ov004_0221d050(void *);
#define INIT(i, a, b, c)                                                                                                      \
    {                                                                                                                         \
        Vec *v = &data_ov004_02257a94[i];                                                                                     \
        v->x = (a);                                                                                                           \
        v->y = (b);                                                                                                           \
        v->z = (c);                                                                                                           \
        __register_global_object(v, func_020012dc, data_ov004_02257a24[i]);                                                   \
    }
int func_ov004_0221d2d0(u8 *self)
{
    Vec candidate;
    unsigned i;
    if (!func_0202e364(self)) {
        return 0;
    }
    ((Vec *) (self + 0x5c))->x = data_020ca0e4 + 0x1000;
    ((Vec *) (self + 0x5c))->z = data_020ca0e8 - 0x7000;
    if (!(data_ov004_02257a08 & 1)) {
        INIT(0, 0, 0, 0)
        INIT(1, -0x2000, 0, 0)
        INIT(2, -0x4000, 0, 0)
        INIT(3, 0x2000, 0, 0)
        INIT(4, 0, 0, 0x2000)
        INIT(5, -0x2000, 0, 0x2000)
        data_ov004_02257a08 |= 1;
    }
    for (i = 0; i < 6; i++) {
        func_01ffd070(&candidate, (Vec *) (self + 0x5c), &data_ov004_02257a94[i]);
        if (!func_ov004_0223c5a4(&candidate)) {
            ((Vec *) (self + 0x5c))->x = candidate.x;
            ((Vec *) (self + 0x5c))->y = candidate.y;
            ((Vec *) (self + 0x5c))->z = candidate.z;
            break;
        }
    }
    *(short *) (self + 0x8e) = 0;
    func_0201c280(self, self + 0x8a0);
    func_ov004_0221cd48(self + 0x8a0, self);
    if (!func_ov004_0221d068(self + 0x8a0)) {
        func_ov004_0221c844(self, 0);
    } else {
        func_ov004_0221c844(self, 7);
        func_ov004_0221d050(self + 0x8a0);
    }
    data_ov004_02257a18 = self;
    return 1;
}
