/* func_0206aa28 @ 0x0206aa28, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *arg);

class VirtualClass {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7(int arg);
};

struct SomePtr {
    char pad_00[0x14a8];
    VirtualClass *obj;
};

struct SelfType {
    char pad_00[0x24];
    SomePtr *ptr;
    char pad_28[0x10];
    char sub[1];
};

extern "C" void func_0206aa28(SelfType *self)
{
    VirtualClass *obj = self->ptr->obj;
    func_020a8750(&self->sub);
    obj->f7(0);
}
