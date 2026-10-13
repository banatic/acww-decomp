/* func_02069634 @ 0x02069634, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(int *p);

struct Target {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void Method();
};

struct UnkStruct_02069634 {
    char pad_00[0x14a8];
    Target *target;
};

struct UnkStruct_02069634_2 {
    char pad_00[0x24];
    UnkStruct_02069634 *holder;
    char pad_28[0x10];
    int unk_38;
};

extern "C" void func_02069634(UnkStruct_02069634_2 *self)
{
    Target *t = self->holder->target;
    func_020a8750(&self->unk_38);
    t->Method();
}
