/* func_ov116_0229de10 @ 0x0229de10, 0x1a bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

class SubClass {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229de10 {
  public:
    char pad_00[0x94];
    SubClass sub;
};

extern "C" void func_ov002_0220a0ec(SubClass *obj);

extern "C" void func_ov116_0229de10(UnkStruct_0229de10 *self)
{
    func_ov002_0220a0ec(&self->sub);
    self->sub.f3();
}
