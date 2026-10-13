/* func_ov086_02278e6c @ 0x02278e6c, 0x24 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278e6c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    unsigned char pad_04[0xb0 - 4];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov086_02278e6c(UnkStruct_02278e6c *self, int value)
{
    self->f2();
    self->unk_B0 = value;
    self->unk_B4 = -1;
}
