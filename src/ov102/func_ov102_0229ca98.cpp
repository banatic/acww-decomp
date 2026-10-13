/* func_ov102_0229ca98 @ 0x0229ca98, 0x20 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229ca98_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229ca98_2 *obj);

struct UnkStruct_0229ca98 {
    char pad_00[0x2274];
    UnkStruct_0229ca98_2 member;
};

extern "C" void func_ov102_0229ca98(UnkStruct_0229ca98 *self)
{
    func_ov002_0220a0ec(&self->member);
    self->member.f3();
}
