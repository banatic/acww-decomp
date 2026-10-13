/* func_ov111_0229f1d8 @ 0x0229f1d8, 0x24 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f1d8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_0229f1d8_2 {
  public:
    char pad_00[0x3d38];
    UnkStruct_0229f1d8 inner;
};

extern "C" void func_ov002_0220a374(UnkStruct_0229f1d8 *p, int value);

extern "C" void func_ov111_0229f1d8(UnkStruct_0229f1d8_2 *self)
{
    func_ov002_0220a374(&self->inner, 0);
    self->inner.v3();
}
