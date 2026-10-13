/* func_ov128_0229bc30 @ 0x0229bc30, 0x20 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

class UnkStruct_0229bc30 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class Main {
  public:
    char pad_00[0x110];
    UnkStruct_0229bc30 sub;
};

extern "C" void func_ov128_0229bc30(Main *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.f3();
}
