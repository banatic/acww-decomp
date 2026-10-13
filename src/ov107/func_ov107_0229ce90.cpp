/* func_ov107_0229ce90 @ 0x0229ce90, 0x24 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ce90 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov002_0220a374(UnkStruct_0229ce90 *, int);

struct UnkStruct_0229ce90_2 {
    char pad_00[0x22b4];
    UnkStruct_0229ce90 sub;
};

extern "C" void func_ov107_0229ce90(UnkStruct_0229ce90_2 *obj)
{
    func_ov002_0220a374(&obj->sub, 0);
    obj->sub.f3();
}
