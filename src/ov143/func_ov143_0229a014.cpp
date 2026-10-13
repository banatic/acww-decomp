/* func_ov143_0229a014 @ 0x0229a014, 0x1c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

struct SubClass {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229a014 {
    char pad_00[0xAC];
    SubClass sub;
};

extern "C" void func_ov002_0220a374(SubClass *, int);

extern "C" void func_ov143_0229a014(UnkStruct_0229a014 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.f3();
}
