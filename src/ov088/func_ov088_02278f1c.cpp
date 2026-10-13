/* func_ov088_02278f1c @ 0x02278f1c, 0x50 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f1c {
  public:
    virtual void vfunc_00();

  private:
    char pad[0xb0 - 4];

  public:
    int field_b0;
};

typedef void (UnkStruct_02278f1c::*PMF)();

struct PMFEntry {
    PMF pmf;
    int pad_08;
};

extern unsigned char data_ov088_02279c1c[];
extern PMFEntry data_ov088_02279c14[];
extern "C" void func_ov088_02278f0c(UnkStruct_02278f1c *self, int arg);

extern "C" void func_ov088_02278f1c(UnkStruct_02278f1c *self)
{
    int idx = self->field_b0;
    if (data_ov088_02279c1c[12 * idx]) {
        return;
    }
    if (data_ov088_02279c14[idx].pmf == 0) {
        return;
    }
    (self->*data_ov088_02279c14[idx].pmf)();
    func_ov088_02278f0c(self, 0);
}
