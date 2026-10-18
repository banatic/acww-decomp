/* func_ov121_0229a358 @ 0x0229a358, 0x24 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

struct SubStruct {
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
};

struct UnkStruct_0229a358 {
    char pad_00[0x3a8];
    SubStruct sub;
};

extern "C" void func_ov121_0229a358(UnkStruct_0229a358 *arg)
{
    func_ov002_0220a374(&arg->sub, 0);
    arg->sub.f4();
}
