/* func_ov004_02247028 @ 0x02247028, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02247028 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02247028_2 {
    u8 pad_00[0x110];
    struct UnkStruct_02247028 pos;
};

extern struct UnkStruct_02247028 data_ov004_0224de64;
extern void func_0203be6c(struct UnkStruct_02247028_2 *self);
extern void func_01ffcbb0(struct UnkStruct_02247028 *out, struct UnkStruct_02247028_2 *self);
extern int func_0203c57c(struct UnkStruct_02247028_2 *self);
extern int func_0203c568(struct UnkStruct_02247028_2 *self);
extern int func_0203c548(struct UnkStruct_02247028_2 *self);
extern void func_0203bd84(struct UnkStruct_02247028_2 *self, struct UnkStruct_02247028 *v, int a, int b, int c);

void func_ov004_02247028(struct UnkStruct_02247028_2 *self)
{
    struct UnkStruct_02247028 v;

    self->pos.x = data_ov004_0224de64.x;
    self->pos.y = data_ov004_0224de64.y;
    self->pos.z = data_ov004_0224de64.z;
    func_0203be6c(self);
    func_01ffcbb0(&v, self);
    func_0203bd84(self, &v, func_0203c57c(self), func_0203c568(self), func_0203c548(self));
}
