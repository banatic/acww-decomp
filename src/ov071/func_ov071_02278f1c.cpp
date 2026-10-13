/* func_ov071_02278f1c @ 0x02278f1c, 0x28 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

class Class_ov071 {
  public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    unsigned char pad_04[0xac];
    int unk_B0;
    void *unk_B4;
    unsigned char unk_B8;
};

extern "C" void func_ov071_02278f1c(Class_ov071 *self, void *arg)
{
    self->m2();
    self->unk_B4 = arg;
    self->unk_B0 = 0;
    self->unk_B8 = 0;
}
