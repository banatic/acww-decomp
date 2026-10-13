/* func_ov129_0229c348 @ 0x0229c348, 0x20 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c348 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229c348_2 {
    char pad_00[0x3a0];
    UnkStruct_0229c348 sub;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229c348 *sub);

extern "C" void func_ov129_0229c348(UnkStruct_0229c348_2 *p)
{
    func_ov002_0220a0ec(&p->sub);
    p->sub.f3();
}
