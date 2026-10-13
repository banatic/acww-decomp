/* func_ov128_0229bce4 @ 0x0229bce4, 0x24 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

class SubObject {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

struct UnkStruct_0229bce4 {
    char pad_00[0x110];
    SubObject sub;
};

extern "C" void func_ov002_0220a374(SubObject *, int);

extern "C" void func_ov128_0229bce4(UnkStruct_0229bce4 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.vf3();
}
