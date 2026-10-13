/* func_ov100_0229ca7c @ 0x0229ca7c, 0x20 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *p);

class UnkStruct_0229ca7c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229ca7c_2 {
    char pad_00[0x2274];
    UnkStruct_0229ca7c sub;
};

extern "C" void func_ov100_0229ca7c(UnkStruct_0229ca7c_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.f3();
}
