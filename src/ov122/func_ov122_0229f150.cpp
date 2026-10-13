/* func_ov122_0229f150 @ 0x0229f150, 0x20 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f150 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_0229f150_2 {
    char pad_00[0x4058];
    UnkStruct_0229f150 member;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229f150 *p);

extern "C" void func_ov122_0229f150(UnkStruct_0229f150_2 *self)
{
    func_ov002_0220a0ec(&self->member);
    self->member.vf3();
}
