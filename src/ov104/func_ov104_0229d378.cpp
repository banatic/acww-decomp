/* func_ov104_0229d378 @ 0x0229d378, 0x24 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d378 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct Container {
    char pad_00[0x24a0];
    UnkStruct_0229d378 member;
};

extern "C" void func_ov002_0220a374(UnkStruct_0229d378 *, int);

extern "C" void func_ov104_0229d378(Container *self)
{
    func_ov002_0220a374(&self->member, 0);
    self->member.m3();
}
