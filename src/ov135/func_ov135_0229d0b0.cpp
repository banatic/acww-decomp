/* func_ov135_0229d0b0 @ 0x0229d0b0, 0x18 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov135_0229d08c(void *);

class SubType {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229d0b0 {
  public:
    char pad_00[0x98];
    SubType sub;
};

extern "C" void func_ov135_0229d0b0(UnkStruct_0229d0b0 *self)
{
    func_ov135_0229d08c(self);
    self->sub.f3();
}
