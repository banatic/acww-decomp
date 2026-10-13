/* func_020044d0 @ 0x020044d0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x, y, z;
};

class UnkStruct_020044d0 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3(const Vec3 *p);
};

extern void *data_021c67a4;
extern Vec3 data_021c67b8;

extern "C" void func_020044d0(UnkStruct_020044d0 *self, const Vec3 *v)
{
    if (v) {
        if (data_021c67a4) {
            Vec3 p;
            p.x = v->x - data_021c67b8.x;
            p.y = v->y - data_021c67b8.y;
            p.z = v->z - data_021c67b8.z;
            self->m3(&p);
        }
    } else {
        self->m3(v);
    }
}
