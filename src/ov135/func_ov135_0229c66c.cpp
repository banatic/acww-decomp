/* func_ov135_0229c66c @ 0x0229c66c, 0x1a bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

class SubClass {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

class OuterClass {
  public:
    char pad_00[0x98];
    SubClass sub;
};

extern "C" void func_ov002_0220a0ec(void *);

extern "C" void func_ov135_0229c66c(OuterClass *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.m3();
}
