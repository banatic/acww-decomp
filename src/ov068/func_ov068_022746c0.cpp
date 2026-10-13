/* func_ov068_022746c0 @ 0x022746c0, 0x1a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022746c0 {
  public:
    virtual void vf0() = 0;
    virtual void vf1() = 0;
    virtual void vf2() = 0;
    char pad_04[0xb0];
    int unk_B4;
};

extern "C" void func_ov068_022746c0(UnkStruct_022746c0 *self, int value)
{
    self->vf2();
    self->unk_B4 = value;
}
