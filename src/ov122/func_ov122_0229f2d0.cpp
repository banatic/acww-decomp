/* func_ov122_0229f2d0 @ 0x0229f2d0, 0x24 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229f2d0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229f2d0_2 {
    char pad_00[0x4058];
    UnkStruct_0229f2d0 inner;
};

extern "C" void func_ov122_0229f2d0(UnkStruct_0229f2d0_2 *self)
{
    func_ov002_0220a374(&self->inner, 0);
    self->inner.f3();
}
