/* func_ov004_0222422c @ 0x0222422c, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0222422c {
  public:
    virtual void vfunc_00();
    char pad_04[0xac];
    int unk_B0;
};

typedef void (UnkStruct_0222422c::*PMF)();

extern unsigned char data_ov004_02254620[];
extern char data_ov004_02254618[];
extern "C" void func_ov004_0222421c(UnkStruct_0222422c *, int);

extern "C" void func_ov004_0222422c(UnkStruct_0222422c *self)
{
    int off = self->unk_B0 * 12;
    if (data_ov004_02254620[off] != 0) {
        return;
    }
    PMF *pmf_ptr = (PMF *) (data_ov004_02254618 + off);
    if (*(int *) pmf_ptr == 0) {
        return;
    }
    (self->*(*pmf_ptr))();
    func_ov004_0222421c(self, 0);
}
