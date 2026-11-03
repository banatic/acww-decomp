/* sound_emitter_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020042c0 @ 0x020042c0, 0x4c bytes, Thumb
 * func_020042b0 @ 0x020042b0, 0x10 bytes, Thumb
 * func_020042a0 @ 0x020042a0, 0x10 bytes, Thumb
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

class UnkStruct_020042b0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(int arg);
};

class UnkStruct_020042a0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int arg);
};

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

extern "C" void func_020042b0(UnkStruct_020042b0 *self, int arg)
{
    self->v4(arg);
}

extern "C" void func_020042a0(UnkStruct_020042a0 *self, int arg)
{
    self->v2(arg);
}
