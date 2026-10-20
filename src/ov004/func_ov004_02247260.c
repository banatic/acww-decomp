/* func_ov004_02247260 @ 0x02247260, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02247260 {
    char unk_00[0x110];
    Vec3 a;
} UnkStruct_02247260;

extern void func_0203be6c(UnkStruct_02247260 *self);
extern void func_01ffcbb0(Vec3 *out, UnkStruct_02247260 *self);
extern int func_0203c57c(UnkStruct_02247260 *self);
extern int func_0203c568(UnkStruct_02247260 *self);
extern int func_0203c548(UnkStruct_02247260 *self);
extern void func_0203bd84(UnkStruct_02247260 *self, Vec3 *v, int a, int b, int c);

void func_ov004_02247260(UnkStruct_02247260 *self)
{
    Vec3 v[2];

    v[0].x = 0;
    v[0].y = 0;
    v[0].z = 0;
    self->a.x = v[0].x;
    self->a.y = v[0].y;
    self->a.z = v[0].z;
    func_0203be6c(self);
    func_01ffcbb0(&v[1], self);
    func_0203bd84(self, &v[1], func_0203c57c(self), func_0203c568(self), func_0203c548(self));
}
