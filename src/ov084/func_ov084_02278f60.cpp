/* func_ov084_02278f60 @ 0x02278f60, 0x24 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f60 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov084_02278f60(UnkStruct_02278f60 *self, int param)
{
    self->f2();
    self->unk_B0 = param;
    self->unk_B4 = -1;
}
