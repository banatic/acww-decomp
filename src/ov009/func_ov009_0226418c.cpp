/* func_ov009_0226418c @ 0x0226418c, 0xd8 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020b30e8(unsigned short, unsigned int);

class CEx {
  public:
    virtual void vfunc_00();
    unsigned char pad_04[0x130];
    unsigned char unk_134;
    unsigned short unk_136;
};

typedef int (CEx::*PMF)();

extern PMF data_ov009_02265890, data_ov009_022657e8, data_ov009_02265800, data_ov009_02265878, data_ov009_02265870,
    data_ov009_02265868, data_ov009_02265860;

extern "C" int func_ov009_0226418c(CEx *self, unsigned int idx)
{
    static PMF table[7] = {data_ov009_02265890, data_ov009_022657e8, data_ov009_02265800, data_ov009_02265878,
                           data_ov009_02265870, data_ov009_02265868, data_ov009_02265860};
    if (idx >= 7) {
        goto fail;
    }
    if ((self->*table[idx])() == 0) {
        goto fail;
    }
    if (func_020b30e8(self->unk_136, idx) == 0) {
        goto fail;
    }
    self->unk_134 = (unsigned char) idx;
    return 1;
fail:
    return 0;
}
