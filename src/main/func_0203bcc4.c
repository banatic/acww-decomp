/* func_0203bcc4 @ 0x0203bcc4, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

extern int func_0203f844(void *slot, Vec *v);
extern void func_020ea634(int *v, int angle);
extern void func_020eaca0(Vec *d, Vec *a, Vec *b);
extern int VEC_Mag(Vec *v);
extern s16 FX_SinCosTable_[];
extern Vec data_021c67d0;
extern Vec data_021c67b8;
extern int data_021c679c;

void func_0203bcc4(u8 *self, Vec *a, Vec *b)
{
    int r;
    int k;
    Vec t;

    r = func_0203f844(self + 0x188, a);
    func_0203f844(self + 0x194, b);
    *(int *) (self + 0x1a0) = 0;
    *(int *) (self + 0x1a4) = 0x1000;
    *(int *) (self + 0x1a8) = 0;
    k = (int) (u16) r >> 4;
    *(int *) (self + 0x1a4) = FX_SinCosTable_[k * 2 + 1];
    *(int *) (self + 0x1a8) = FX_SinCosTable_[k * 2];
    func_020ea634((int *) (self + 0x1a0), *(s16 *) (self + 0x174));
    data_021c67d0.x = a->x;
    data_021c67d0.y = a->y;
    data_021c67d0.z = a->z;
    data_021c67b8.x = b->x;
    data_021c67b8.y = b->y;
    data_021c67b8.z = b->z;
    func_020eaca0(&t, a, b);
    data_021c679c = VEC_Mag(&t);
}
