/* func_ov100_0229e3b0 @ 0x0229e3b0, 0x1c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov100_0229e374(void *self);

class CSub {
  public:
    virtual void f0() {}
    virtual void f1() {}
    virtual void f2() {}
    virtual void f3() {}
};

class UnkStruct_0229e3b0 {
  public:
    char pad_00[0x2274];
    CSub sub;
};

extern "C" void func_ov100_0229e3b0(UnkStruct_0229e3b0 *self)
{
    func_ov100_0229e374(self);
    self->sub.f3();
}
