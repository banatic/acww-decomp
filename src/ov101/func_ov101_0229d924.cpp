/* func_ov101_0229d924 @ 0x0229d924, 0x1c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov101_0229d8e0(void *);

class VirtualBase {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

class UnkStruct_0229d924 {
  public:
    char pad_00[0x229c];
    VirtualBase vb;
};

extern "C" void func_ov101_0229d924(UnkStruct_0229d924 *self)
{
    func_ov101_0229d8e0(self);
    self->vb.m3();
}
