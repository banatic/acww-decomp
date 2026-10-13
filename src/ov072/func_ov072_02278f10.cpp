/* func_ov072_02278f10 @ 0x02278f10, 0x50 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov072_02278f00(void *, int);

class UnkStruct_02278f10 {
  public:
    virtual void vfunc_00();
};

struct PMFData {
    void (UnkStruct_02278f10::*pmf)();
    int extra;
};

extern unsigned char data_ov072_02279a2c[];
extern PMFData data_ov072_02279a24[];

extern "C" void func_ov072_02278f10(UnkStruct_02278f10 *self)
{
    int idx = *((int *) ((char *) self + 0xB0));
    if (data_ov072_02279a2c[idx * 12] != 0) {
        return;
    }
    if (data_ov072_02279a24[idx].pmf == 0) {
        return;
    }
    (self->*data_ov072_02279a24[idx].pmf)();
    func_ov072_02278f00(self, 0);
}
