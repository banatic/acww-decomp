/* func_ov100_0229cc3c @ 0x0229cc3c, 0x24 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229cc3c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov002_0220a374(UnkStruct_0229cc3c *sub, int flag);

struct Parent {
    char pad_00[0x2274];
    UnkStruct_0229cc3c sub;
};

extern "C" void func_ov100_0229cc3c(Parent *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.f3();
}
