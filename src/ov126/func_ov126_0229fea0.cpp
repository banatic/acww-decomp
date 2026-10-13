/* func_ov126_0229fea0 @ 0x0229fea0, 0x20 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229fea0 {
  public:
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229fea0 *p);

struct UnkStruct_0229fea0_2 {
    char pad_00[0x3f90];
    UnkStruct_0229fea0 sub;
};

extern "C" void func_ov126_0229fea0(UnkStruct_0229fea0_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    (&self->sub)->v4();
}
