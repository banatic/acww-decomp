/* func_ov141_0229a44c @ 0x0229a44c, 0x24 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *ptr, int arg);

struct Member {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct Parent {
    char pad_00[0xa38];
    Member member;
};

extern "C" void func_ov141_0229a44c(Parent *self)
{
    func_ov002_0220a374(&self->member, 0);
    self->member.f3();
}
