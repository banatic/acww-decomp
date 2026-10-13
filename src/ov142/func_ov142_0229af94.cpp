/* func_ov142_0229af94 @ 0x0229af94, 0x1c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229af94 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229af94_2 {
    char pad_00[0xE8];
    UnkStruct_0229af94 sub;
};

extern "C" void func_ov142_0229af94(UnkStruct_0229af94_2 *p)
{
    func_ov002_0220a374(&p->sub, 0);
    p->sub.v3();
}
