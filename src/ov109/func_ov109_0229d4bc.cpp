/* func_ov109_0229d4bc @ 0x0229d4bc, 0x1c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d4bc {
  public:
    virtual void f0() {}
    virtual void f1() {}
    virtual void f2() {}
    virtual void f3() {}
};

class Parent {
  public:
    char pad_00[0x2274];
    UnkStruct_0229d4bc sub;
};

extern "C" void func_ov109_0229d478(Parent *p);

extern "C" void func_ov109_0229d4bc(Parent *self)
{
    func_ov109_0229d478(self);
    self->sub.f3();
}
