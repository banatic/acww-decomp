/* func_ov082_02279018 @ 0x02279018, 0x2a bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

class FuncClass {
  public:
    virtual void VirtualA();
    virtual void VirtualB();
    virtual void VirtualC();
    unsigned char pad_04[0xb0 - 4];
    int unk_B0;
    unsigned char pad_B4[0xc6 - 0xb4];
    unsigned char unk_C6;
    int unk_C8;
};

extern "C" void func_ov082_02279018(FuncClass *self, int val)
{
    self->VirtualC();
    self->unk_B0 = val;
    self->unk_C6 = 0;
    self->unk_C8 = -1;
}
