/* func_0206b024 @ 0x0206b024, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *p);

class UnkStruct_0206b024 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void target(int arg);
};

struct Container {
    char pad_00[0x14a8];
    UnkStruct_0206b024 *obj;
};

struct UnkStruct_0206b024_2 {
    char pad_00[0x24];
    Container *container;
    char pad_28[0x10];
    char sub;
    int arg;
};

extern "C" void func_0206b024(UnkStruct_0206b024_2 *self)
{
    int a = self->arg;
    UnkStruct_0206b024 *v = self->container->obj;
    func_020a8750(&self->sub);
    v->target(a);
}
