/* func_ov079_02278c7c @ 0x02278c7c, 0x30 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278c7c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    unsigned char pad_04[0xac];
    int unk_B0;
    unsigned char pad_B4[0x10];
    unsigned short unk_C4;
    unsigned char pad_C6[2];
    int unk_C8;
};

extern "C" void func_ov079_02278c7c(UnkStruct_02278c7c *self, int param)
{
    self->v2();
    self->unk_B0 = param;
    self->unk_C4 = 0xfff1;
    self->unk_C8 = -1;
}
