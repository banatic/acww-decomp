/* func_ov146_0229aca0 @ 0x0229aca0, 0x24 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov146_0229a400(struct UnkStruct_0229aca0 *);
extern "C" void func_ov146_022997c8(struct UnkStruct_0229aca0 *);

class UnkStruct_0229aca0_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct UnkStruct_0229aca0 {
    char pad_00[0x1fb4];
    UnkStruct_0229aca0_2 unk_1FB4;
};

extern "C" void func_ov146_0229aca0(struct UnkStruct_0229aca0 *a)
{
    func_ov146_0229a400(a);
    func_ov146_022997c8(a);
    a->unk_1FB4.m3();
}
