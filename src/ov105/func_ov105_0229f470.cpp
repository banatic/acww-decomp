/* func_ov105_0229f470 @ 0x0229f470, 0x194 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

class PmfBase {
  public:
    void n0() {}
};
typedef void (PmfBase::*PMF)();

extern "C" void func_ov105_0229eaa4(void *self);
extern "C" void func_ov105_0229ea6c(void *self);

struct UnkStruct_0229f470 {
    char pad_00[0x8c];
    unsigned char idx;
};

extern "C" int func_ov105_0229f470(UnkStruct_0229f470 *self)
{
    static PMF tbl[22] = {&PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0,
                          &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0,
                          &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0,
                          &PmfBase::n0, &PmfBase::n0, &PmfBase::n0, &PmfBase::n0};

    func_ov105_0229eaa4(self);
    (((PmfBase *) self)->*tbl[self->idx])();
    func_ov105_0229ea6c(self);
    return 1;
}
