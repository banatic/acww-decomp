/* func_ov105_0229eaec @ 0x0229eaec, 0x1c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov105_0229eaa4(void *p);

class UnkStruct_0229eaec {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct UnkStruct_0229eaec_2 {
    unsigned char pad_00[0x24a4];
    UnkStruct_0229eaec v;
};

extern "C" int func_ov105_0229eaec(UnkStruct_0229eaec_2 *p)
{
    func_ov105_0229eaa4(p);
    return p->v.m3();
}
