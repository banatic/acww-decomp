/* func_ov141_0229a3a4 @ 0x0229a3a4, 0x20 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229a3a4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct Parent {
    char pad_00[0xa38];
    UnkStruct_0229a3a4 obj;
};

extern "C" void func_ov002_0220a0ec(void *);

extern "C" void func_ov141_0229a3a4(Parent *p)
{
    func_ov002_0220a0ec(&p->obj);
    p->obj.f3();
}
