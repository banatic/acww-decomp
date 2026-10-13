/* func_ov118_0229a92c @ 0x0229a92c, 0x24 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229a92c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229a92c_2 {
    char pad_00[0x6c0];
    UnkStruct_0229a92c obj;
};

extern "C" void func_ov002_0220a374(void *ptr, int arg);

extern "C" void func_ov118_0229a92c(UnkStruct_0229a92c_2 *self)
{
    func_ov002_0220a374(&self->obj, 0);
    self->obj.f3();
}
