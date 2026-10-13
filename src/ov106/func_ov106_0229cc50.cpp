/* func_ov106_0229cc50 @ 0x0229cc50, 0x24 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229cc50 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct BigStruct {
    char pad_00[0x22a0];
    UnkStruct_0229cc50 sub;
};

extern "C" void func_ov106_0229cc50(BigStruct *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.f3();
}
