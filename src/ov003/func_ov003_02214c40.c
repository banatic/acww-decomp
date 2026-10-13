/* func_ov003_02214c40 @ 0x02214c40, 0xec bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern void func_0200ee40(void *self);
extern int func_0200f554(void *self);
extern void func_02010d64(void *self);
extern int func_02073908(int a, int b);
extern void func_ov003_02214d2c(void *self);
extern int func_02008258(void *self, int a);
extern void func_0200faf0(void *self, int a);

extern int data_020ccf94;

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
    char pad_6C8[0x7f0 - 0x6c8];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02214c40;

void func_ov003_02214c40(UnkStruct_02214c40 *self)
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
    func_0200f554(self);
    func_02010d64(self);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02214d2c(self);
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200faf0(self, 0x400);
    }
    self->v.x = sv.x;
    self->v.y = sv.y;
    self->v.z = sv.z;
    self->d0 = d;
    self->a = sa;
    self->b = sb;
}
