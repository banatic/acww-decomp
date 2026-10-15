/* func_ov003_02229f2c @ 0x02229f2c, 0x15c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_02229f2c;
typedef struct {
    char pad_00[0x34];
    int r;
    char pad_38[8];
} UnkStruct_02229f2c_2;
typedef struct {
    u16 v;
    char pad_02[18];
} UnkStruct_02229f2c_3;

typedef struct {
    char pad_00[0x120];
    int unk_120;
    char pad_124[4];
    int unk_128;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[0x1ff - 0x13a];
    u8 kind;
} UnkStruct_02229f2c_4;

extern s16 FX_SinCosTable_[];
extern UnkStruct_02229f2c_3 data_ov003_0223c024[];
extern int func_02034270(UnkStruct_02229f2c_2 *out, UnkStruct_02229f2c *p, int a, int b);
extern void func_0203423c(UnkStruct_02229f2c_2 *p);

void func_ov003_02229f2c(UnkStruct_02229f2c_4 *self, int *o1, int *o2, int *o3)
{
    UnkStruct_02229f2c pa, pb, pc;
    UnkStruct_02229f2c_2 b1, b2, b3;
    int t;
    int zz;
    int zz2;
    int t2;
    int zz3;
    int t3;
    int rad;
    int a;

    a = self->unk_138;
    t = ((u16) (s16) (a + 0x2000) >> 4) << 1;
    rad = data_ov003_0223c024[self->kind].v;
    zz = self->unk_128 + FX_SinCosTable_[t + 1] * rad / 100;
    pa.x = self->unk_120 + FX_SinCosTable_[t] * rad / 100;
    pa.y = -0x1333;
    pa.z = zz;
    t2 = ((u16) (s16) (a - 0x2000) >> 4) << 1;
    zz2 = self->unk_128 + FX_SinCosTable_[t2 + 1] * rad / 100;
    pb.x = self->unk_120 + FX_SinCosTable_[t2] * rad / 100;
    pb.y = -0x1333;
    pb.z = zz2;
    t3 = ((u16) self->unk_138 >> 4) << 1;
    zz3 = self->unk_128 + FX_SinCosTable_[t3 + 1] * rad / 100;
    pc.x = self->unk_120 + FX_SinCosTable_[t3] * rad / 100;
    pc.y = -0x1333;
    pc.z = zz3;
    func_02034270(&b1, &pa, 0, 0);
    func_02034270(&b2, &pb, 0, 0);
    func_02034270(&b3, &pc, 0, 0);
    *o1 = b1.r;
    *o2 = b2.r;
    *o3 = b3.r;
    func_0203423c(&b3);
    func_0203423c(&b2);
    func_0203423c(&b1);
}
