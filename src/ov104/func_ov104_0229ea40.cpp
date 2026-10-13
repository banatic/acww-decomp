/* func_ov104_0229ea40 @ 0x0229ea40, 0x1c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov104_0229e9f8(struct UnkStruct_0229ea40 *p);

struct UnkStruct_0229ea40_2 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229ea40 {
    char pad_00[0x24a0];
    UnkStruct_0229ea40_2 member;
};

extern "C" void func_ov104_0229ea40(UnkStruct_0229ea40 *a)
{
    func_ov104_0229e9f8(a);
    a->member.f3();
}
