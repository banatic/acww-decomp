/* func_ov003_02228ae8 @ 0x02228ae8, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02228ae8;
struct UnkStruct_02228ae8_2;
typedef void (UnkStruct_02228ae8::*PMF)(UnkStruct_02228ae8_2 *, int);

struct UnkStruct_02228ae8_3 {
    PMF a;
    PMF b;
};
extern UnkStruct_02228ae8_3 data_ov003_0225f1d0[];

struct Vec3 {
    int x, y, z;
};

extern "C" {

void func_020044d0(UnkStruct_02228ae8_2 *self, Vec3 *v);
void func_020042c0(void *p, Vec3 *v);
void func_ov003_022279d8(UnkStruct_02228ae8_2 *self);

void func_ov003_02228ae8(UnkStruct_02228ae8 *obj, UnkStruct_02228ae8_2 *self, int c)
{
    Vec3 v;
    Vec3 w;
    Vec3 *p;

    p = (Vec3 *) ((char *) self + 0x120);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    func_020044d0(self, &v);
    p = (Vec3 *) ((char *) self + 0x120);
    w.x = p->x;
    w.y = p->y;
    w.z = p->z;
    func_020042c0((char *) self + 0x40, &w);
    if (data_ov003_0225f1d0[*(int *) ((char *) self + 0x80)].b) {
        (obj->*data_ov003_0225f1d0[*(int *) ((char *) self + 0x80)].b)(self, c);
    }
    func_ov003_022279d8(self);
}
}
