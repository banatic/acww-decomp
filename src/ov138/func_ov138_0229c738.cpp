/* func_ov138_0229c738 @ 0x0229c738, 0x1c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c738 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct Parent {
    char pad_00[0x98];
    UnkStruct_0229c738 sub;
};

extern "C" void func_ov002_0220a374(UnkStruct_0229c738 *sub, int arg);

extern "C" int func_ov138_0229c738(Parent *parent)
{
    func_ov002_0220a374(&parent->sub, 0);
    return parent->sub.m3();
}
