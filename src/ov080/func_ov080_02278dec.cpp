/* func_ov080_02278dec @ 0x02278dec, 0x24 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278dec {
  public:
    virtual void f0();
    virtual void f1();
    virtual void method();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov080_02278dec(UnkStruct_02278dec *self, int param)
{
    self->method();
    self->unk_B0 = param;
    self->unk_B4 = -1;
}
