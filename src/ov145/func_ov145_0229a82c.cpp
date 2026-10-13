/* func_ov145_0229a82c @ 0x0229a82c, 0x18 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov145_0229a7d8(void *p);

class UnkStruct_0229a82c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229a82c_2 {
    char pad_00[0xc8];
    UnkStruct_0229a82c obj;
};

extern "C" void func_ov145_0229a82c(UnkStruct_0229a82c_2 *s)
{
    func_ov145_0229a7d8(s);
    s->obj.f3();
}
