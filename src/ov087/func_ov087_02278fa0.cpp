/* func_ov087_02278fa0 @ 0x02278fa0, 0x1a bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278fa0 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    char pad_04[0xAC];
    int unk_B0;
};

extern "C" void func_ov087_02278fa0(UnkStruct_02278fa0 *self, int val)
{
    self->vf2();
    self->unk_B0 = val;
}
