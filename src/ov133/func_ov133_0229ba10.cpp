/* func_ov133_0229ba10 @ 0x0229ba10, 0x24 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ba10 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229ba10_2 {
    char pad_00[0x11c];
    UnkStruct_0229ba10 obj;
};

extern "C" void func_ov002_0220a374(void *ptr, int arg);

extern "C" void func_ov133_0229ba10(UnkStruct_0229ba10_2 *self)
{
    func_ov002_0220a374(&self->obj, 0);
    self->obj.f3();
}
