/* func_ov113_022998ac @ 0x022998ac, 0x20 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

struct SubClass {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};
struct MainClass {
    char pad_00[0x2b20];
    SubClass sub;
};
extern "C" void func_ov002_0220a0ec(SubClass *);
extern "C" void func_ov113_022998ac(MainClass *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.f3();
}
