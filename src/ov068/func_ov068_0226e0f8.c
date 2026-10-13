/* func_ov068_0226e0f8 @ 0x0226e0f8, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x5c];
    Vec3 sub;
} Other;
typedef struct {
    char pad_00[0x21c];
    Other *ptr;
} UnkStruct_0226e0f8;

extern void func_0203bc50(UnkStruct_0226e0f8 *self, Vec3 *v);
extern void func_0203be6c(UnkStruct_0226e0f8 *self);
extern void func_01ffcbb0(int *buf, UnkStruct_0226e0f8 *self);
extern int func_0203c57c(UnkStruct_0226e0f8 *self);
extern int func_0203c568(UnkStruct_0226e0f8 *self);
extern int func_0203c548(UnkStruct_0226e0f8 *self);
extern void func_0203bd84(UnkStruct_0226e0f8 *self, int *buf, int a, int b, int c);

void func_ov068_0226e0f8(UnkStruct_0226e0f8 *self)
{
    Other *other;
    Vec3 *sub;
    int a, b, c;
    Vec3 v;
    int buf[4];

    other = self->ptr;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    if (other != 0) {
        sub = &other->sub;
        v.x = other->sub.x;
        v.y = sub->y;
        v.z = sub->z;
    }
    func_0203bc50(self, &v);
    func_0203be6c(self);
    func_01ffcbb0(buf, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    c = func_0203c548(self);
    func_0203bd84(self, buf, a, b, c);
}
