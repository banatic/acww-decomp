/* func_ov103_0229c7ec @ 0x0229c7ec, 0x24 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229c7ec {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229c7ec_2 {
    unsigned char pad_00[0x2274];
    UnkStruct_0229c7ec inner;
};

extern "C" void func_ov103_0229c7ec(UnkStruct_0229c7ec_2 *self)
{
    func_ov002_0220a374(&self->inner, 0);
    self->inner.f3();
}
