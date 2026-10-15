/* func_ov003_02218ff0 @ 0x02218ff0, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern void func_0200ee40(void *self);
extern int func_0200f554(void *self);
extern void func_02010d64(void *self);
extern int func_0201100c(void *self);
extern void func_ov003_022191c0(void *self);
extern void func_ov003_022190b0(void *self);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} Mtx;

typedef struct {
    char pad_00[0xc4];
    Vec3 v;
    short d0;
    char pad_D2[0x298 - 0xd2];
    Mtx a;
    char pad_2C8[0x698 - 0x2c8];
    Mtx b;
} UnkStruct_02218ff0;

void func_ov003_02218ff0(UnkStruct_02218ff0 *self)
{
    Vec3 *p;
    volatile Vec3 sv;
    short d;
    Mtx sa, sb;

    func_02010f5c(self);
    p = &self->v;
    sv.x = self->v.x;
    sv.y = p->y;
    sv.z = p->z;
    d = self->d0;
    sa = self->a;
    sb = self->b;
    func_0200ee40(self);
    func_ov003_022191c0(self);
    self->v.x = sv.x;
    self->v.y = sv.y;
    self->v.z = sv.z;
    self->d0 = d;
    self->a = sa;
    self->b = sb;
    if (func_0200f554(self) != 0) {
        func_0201100c(self);
    }
    func_02010d64(self);
    func_ov003_022190b0(self);
}
