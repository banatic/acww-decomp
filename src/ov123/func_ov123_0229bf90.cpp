/* func_ov123_0229bf90 @ 0x0229bf90, 0x1c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229bf90 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229bf90_2 {
    char pad_00[0x1cc];
    UnkStruct_0229bf90 inner;
};

extern "C" void func_ov123_0229bf64(UnkStruct_0229bf90_2 *self);

extern "C" void func_ov123_0229bf90(UnkStruct_0229bf90_2 *self)
{
    UnkStruct_0229bf90 *p;
    func_ov123_0229bf64(self);
    p = &self->inner;
    p->v3();
}
