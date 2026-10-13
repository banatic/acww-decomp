/* func_ov004_02246ef4 @ 0x02246ef4, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02246ef4 {
    char unk_00[0x110];
    Vec3 a;
    char unk_11C[0x1cc - 0x11c];
    Vec3 b;
} UnkStruct_02246ef4;

extern void func_0203be6c(UnkStruct_02246ef4 *self);
extern void func_01ffcbb0(Vec3 *out, UnkStruct_02246ef4 *self);
extern int func_0203c57c(UnkStruct_02246ef4 *self);
extern int func_0203c568(UnkStruct_02246ef4 *self);
extern int func_0203c548(UnkStruct_02246ef4 *self);
extern void func_0203bd84(UnkStruct_02246ef4 *self, Vec3 *v, int a, int b, int c);

void func_ov004_02246ef4(UnkStruct_02246ef4 *self)
{
    Vec3 v;

    self->a.x = self->b.x;
    self->a.y = self->b.y;
    self->a.z = self->b.z;
    func_0203be6c(self);
    func_01ffcbb0(&v, self);
    func_0203bd84(self, &v, func_0203c57c(self), func_0203c568(self), func_0203c548(self));
}
