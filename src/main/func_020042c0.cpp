/* func_020042c0 @ 0x020042c0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};

class GameObject {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void method(Vec *v);
};

extern int data_021c67a4;
extern Vec data_021c67b8;

extern "C" void func_020042c0(GameObject *obj, Vec *arg)
{
    if (arg) {
        if (data_021c67a4) {
            Vec local;
            local.x = arg->x - data_021c67b8.x;
            local.y = arg->y - data_021c67b8.y;
            local.z = arg->z - data_021c67b8.z;
            obj->method(&local);
        }
    } else {
        obj->method(arg);
    }
}
