/* func_ov110_0229ca28 @ 0x0229ca28, 0x20 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);
struct UnkStruct_0229ca28 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};
struct Big {
    char pad_00[0x22e0];
    UnkStruct_0229ca28 obj;
};
extern "C" void func_ov110_0229ca28(Big *param)
{
    func_ov002_0220a0ec(&param->obj);
    param->obj.f3();
}
