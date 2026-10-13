/* func_ov088_02278c94 @ 0x02278c94, 0x44 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *MI_CpuFill8(void *, int, unsigned int);

class UnkStruct_02278c94 {
  public:
    virtual void f1();
    virtual void f2();
    virtual void f3();
    char pad_04[0xb4];
    int unk_B8;
};

extern "C" void func_ov088_02278c94(UnkStruct_02278c94 *self, int value)
{
    self->f3();
    self->unk_B8 = value;
    *((char *) self->unk_B8 + 0x739) = 0;
    MI_CpuFill8((char *) self + 0xbd, 0, 0x1e);
    MI_CpuFill8((char *) self + 0xdb, 0xff, 5);
}
