/* func_ov003_0221e32c @ 0x0221e32c, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" int func_020b30e8(u16, unsigned int);

class UnkStruct_0221e32c {
  public:
    u8 pad_00[0x134];
    u8 unk_134;
    u8 pad_135;
    u16 unk_136;
    int method();
};

typedef int (UnkStruct_0221e32c::*PMF)();

extern PMF data_ov003_022393fc;
extern PMF data_ov003_0223940c;
extern PMF data_ov003_0223945c;
extern PMF data_ov003_02239454;
extern PMF data_ov003_022393c4;
extern PMF data_ov003_022393bc;
extern PMF data_ov003_022393b4;

extern "C" int func_ov003_0221e32c(UnkStruct_0221e32c *self, unsigned int index)
{
    static PMF s_tbl[7] = {data_ov003_022393fc, data_ov003_0223940c, data_ov003_0223945c, data_ov003_02239454,
                           data_ov003_022393c4, data_ov003_022393bc, data_ov003_022393b4};

    if (index >= 7) {
        goto fail;
    }
    if ((self->*s_tbl[index])() == 0) {
        goto fail;
    }
    if (func_020b30e8(self->unk_136, index) == 0) {
        goto fail;
    }

    self->unk_134 = (u8) index;
    return 1;

fail:
    return 0;
}
