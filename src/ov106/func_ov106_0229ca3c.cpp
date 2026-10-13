/* func_ov106_0229ca3c @ 0x0229ca3c, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

class SubClass {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct MyBase {
    char pad_00[0x22a0];
    SubClass sub;
};

extern "C" void func_ov002_0220a0ec(SubClass *p);

extern "C" void func_ov106_0229ca3c(MyBase *obj)
{
    func_ov002_0220a0ec(&obj->sub);
    obj->sub.v3();
}
