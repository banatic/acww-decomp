/* func_ov068_0226dcc0 @ 0x0226dcc0, 0x74 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;

extern Vec data_021fbee8; // 0x021fbee8
extern int func_ov068_0226dabc(void *);
extern void func_0203be6c(void *);
extern void func_01ffcbb0(Vec *, void *);
extern int func_0203c57c(void *);
extern int func_0203c568(void *);
extern int func_0203c548(void *);
extern void func_0203bd84(void *, Vec *, int, int, int);

typedef struct {
    char pad_00[0x110];
    fx32 unk_110, unk_114, unk_118;
} UnkStruct_0226dcc0;

void func_ov068_0226dcc0(UnkStruct_0226dcc0 *self)
{
    Vec loc;
    int a, b;
    self->unk_110 = data_021fbee8.x;
    self->unk_114 = data_021fbee8.y;
    self->unk_118 = data_021fbee8.z;
    self->unk_114 += func_ov068_0226dabc(self);
    func_0203be6c(self);
    func_01ffcbb0(&loc, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    func_0203bd84(self, &loc, a, b, func_0203c548(self));
}
