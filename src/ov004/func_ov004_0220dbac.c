/* func_ov004_0220dbac @ 0x0220dbac, 0x1d4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern unsigned int data_ov004_02256c80, data_ov004_02256c64, data_ov004_02256c8c;
extern Vec data_ov004_02256e28[2], data_ov004_02256e40[2], data_ov004_02256db0;
extern u8 data_ov004_02256cc0[], data_ov004_02256d08[], data_ov004_02256d5c[], data_ov004_02256d68[], data_ov004_02256da4[],
    data_021fbe48[];
extern void __register_global_object(void *, void *destructor, void *);
extern void func_020012dc(void *);
extern void func_020e9640(void *, int), MTX_MultVec43(Vec *, void *, Vec *);
extern void func_ov004_0220ff74(void *, Vec *, Vec *);
extern int func_020ea9e4(Vec *, Vec *), func_020eaa2c(Vec *, Vec *);
extern void VEC_Subtract(Vec *, Vec *, Vec *), VEC_Add(Vec *, Vec *, Vec *);

void func_ov004_0220dbac(u8 *self, u8 *other)
{
    Vec offset, point;
    int distance;
    if (W(P(self, 0x9c), 0x784) != 1) {
        return;
    }
    if (!(data_ov004_02256c80 & 1)) {
        data_ov004_02256e28[0].x = 0;
        data_ov004_02256e28[0].y = 0;
        data_ov004_02256e28[0].z = 0;
        __register_global_object(&data_ov004_02256e28[0], ((void *) &func_020012dc), data_ov004_02256cc0);
        {
            Vec *v = &data_ov004_02256e28[1];
            v->x = -0x2000;
            v->y = 0;
            v->z = 0;
            __register_global_object(v, ((void *) &func_020012dc), data_ov004_02256d08);
        }
        data_ov004_02256c80 |= 1;
    }
    if (!(data_ov004_02256c64 & 1)) {
        data_ov004_02256e40[0].x = 0;
        data_ov004_02256e40[0].y = 0;
        data_ov004_02256e40[0].z = 0;
        __register_global_object(&data_ov004_02256e40[0], ((void *) &func_020012dc), data_ov004_02256d5c);
        {
            Vec *v = &data_ov004_02256e40[1];
            v->x = 0x2000;
            v->y = 0;
            v->z = 0;
            __register_global_object(v, ((void *) &func_020012dc), data_ov004_02256d68);
        }
        data_ov004_02256c64 |= 1;
    }
    if (!(data_ov004_02256c8c & 1)) {
        data_ov004_02256db0.x = 0x2000;
        data_ov004_02256db0.y = 0;
        data_ov004_02256db0.z = 0;
        __register_global_object(&data_ov004_02256db0, ((void *) &func_020012dc), data_ov004_02256da4);
        data_ov004_02256c8c |= 1;
    }
    func_020e9640(data_021fbe48, S(P(self, 0x9c), 0x8e));
    MTX_MultVec43(&data_ov004_02256db0, data_021fbe48, &offset);
    func_ov004_0220ff74(P(self, 0x9c), &point, &data_ov004_02256e40[0]);
    distance = func_020ea9e4((Vec *) (other + 0x5c), &point);
    func_ov004_0220ff74(P(self, 0x9c), &point, &data_ov004_02256e40[1]);
    if (distance < func_020ea9e4((Vec *) (other + 0x5c), &point)) {
        if (func_020eaa2c((Vec *) (P(self, 0x9c) + 0x144), &data_ov004_02256e28[0])) {
            Vec *dest = (Vec *) (P(self, 0x9c) + 0x144);
            dest->x = data_ov004_02256e28[0].x;
            dest->y = data_ov004_02256e28[0].y;
            dest->z = data_ov004_02256e28[0].z;
            VEC_Subtract((Vec *) (P(self, 0x9c) + 0x5c), &offset, (Vec *) (P(self, 0x9c) + 0x5c));
        }
    } else {
        if (func_020eaa2c((Vec *) (P(self, 0x9c) + 0x144), &data_ov004_02256e28[1])) {
            Vec *dest = (Vec *) (P(self, 0x9c) + 0x144);
            dest->x = data_ov004_02256e28[1].x;
            dest->y = data_ov004_02256e28[1].y;
            dest->z = data_ov004_02256e28[1].z;
            VEC_Add((Vec *) (P(self, 0x9c) + 0x5c), &offset, (Vec *) (P(self, 0x9c) + 0x5c));
        }
    }
}
