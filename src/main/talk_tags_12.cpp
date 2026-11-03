/* talk_tags_12: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206aa28 @ 0x0206aa28, 0x24 bytes, Thumb
 * func_0206aa04 @ 0x0206aa04, 0x24 bytes, Thumb
 * func_0206a9e0 @ 0x0206a9e0, 0x24 bytes, Thumb
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

class UnkStruct_0206aa04 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual void f4() = 0;
    virtual void f5() = 0;
    virtual void f6() = 0;
    virtual void method(int x) = 0;
};

struct UnkStruct_0206aa04_2 {
    char pad_00[0x14a8];
    UnkStruct_0206aa04 *c;
};

struct UnkStruct_0206aa04_3 {
    char pad_00[0x24];
    UnkStruct_0206aa04_2 *b;
    char pad_28[0x10];
    char sub;
};

class UnkStruct_0206a9e0_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7(int);
};

struct UnkStruct_0206a9e0 {
    char pad_00[0x24];
    void **unk_24;
};

extern "C" void func_0206aa28(SelfType *self)
{
    VirtualClass *obj = self->ptr->obj;
    func_020a8750(&self->sub);
    obj->f7(0);
}

extern "C" void func_0206aa04(UnkStruct_0206aa04_3 *a)
{
    UnkStruct_0206aa04 *c = a->b->c;
    func_020a8750(&a->sub);
    c->method(1);
}

extern "C" void func_0206a9e0(UnkStruct_0206a9e0 *self)
{
    UnkStruct_0206a9e0_2 *obj = (UnkStruct_0206a9e0_2 *) self->unk_24[0x52a];
    func_020a8750((char *) self + 0x38);
    obj->m7(2);
}
