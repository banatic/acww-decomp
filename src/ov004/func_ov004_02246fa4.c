/* func_ov004_02246fa4 @ 0x02246fa4, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02246fa4 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02246fa4_2 {
    u8 pad_00[0x110];
    struct UnkStruct_02246fa4 pos;
};

extern struct UnkStruct_02246fa4 data_ov004_0224de70;
extern void func_0203be6c(struct UnkStruct_02246fa4_2 *self);
extern void func_01ffcbb0(struct UnkStruct_02246fa4 *out, struct UnkStruct_02246fa4_2 *self);
extern int func_0203c57c(struct UnkStruct_02246fa4_2 *self);
extern int func_0203c568(struct UnkStruct_02246fa4_2 *self);
extern int func_0203c548(struct UnkStruct_02246fa4_2 *self);
extern void func_0203bd84(struct UnkStruct_02246fa4_2 *self, struct UnkStruct_02246fa4 *v, int a, int b, int c);

void func_ov004_02246fa4(struct UnkStruct_02246fa4_2 *self)
{
    struct UnkStruct_02246fa4 v;

    self->pos.x = data_ov004_0224de70.x;
    self->pos.y = data_ov004_0224de70.y;
    self->pos.z = data_ov004_0224de70.z;
    func_0203be6c(self);
    func_01ffcbb0(&v, self);
    func_0203bd84(self, &v, func_0203c57c(self), func_0203c568(self), func_0203c548(self));
}
