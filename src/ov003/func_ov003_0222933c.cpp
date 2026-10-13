/* func_ov003_0222933c @ 0x0222933c, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0222933c {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual int get(Vec3 *out);
};

extern "C" {
extern short FX_SinCosTable_[];
extern int func_020e8ed8(int dx, int dz);
extern int FX_MulFunc(int a, int b);

void func_ov003_0222933c(char *self, UnkStruct_0222933c *obj, Vec3 *out)
{
    if (obj->get(out) == 0) {
        Vec3 *q = (Vec3 *) ((char *) obj + 0x5c);
        out->x = q->x;
        out->y = q->y;
        out->z = q->z;
    } else {
        int dx = *(int *) (self + 0x54) - out->x;
        int dz = *(int *) (self + 0x5c) - out->z;
        int k = ((unsigned short) func_020e8ed8(dx, dz) >> 4) << 1;
        out->x += FX_MulFunc(0x4cd, FX_SinCosTable_[k]);
        out->z += FX_MulFunc(0x4cd, FX_SinCosTable_[k + 1]);
    }
}
}
