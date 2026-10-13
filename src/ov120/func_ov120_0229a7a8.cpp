/* func_ov120_0229a7a8 @ 0x0229a7a8, 0x24 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *p, int val);

class UnkStruct_0229a7a8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_0229a7a8_2 {
  public:
    char pad_00[0x6bc];
    UnkStruct_0229a7a8 sub;
};

extern "C" void func_ov120_0229a7a8(UnkStruct_0229a7a8_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}
