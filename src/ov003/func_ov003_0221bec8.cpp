/* func_ov003_0221bec8 @ 0x0221bec8, 0xe0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0221bec8;
typedef void (UnkStruct_0221bec8::*PMF)();

extern PMF data_ov003_022385f0;
extern PMF data_ov003_02238590;
extern PMF data_ov003_02238598;
extern PMF data_ov003_022385a0;
extern PMF data_ov003_022385e0;
extern PMF data_ov003_02238600;
extern PMF data_ov003_02238570;
extern PMF data_ov003_02238588;
extern PMF data_ov003_022385a8;
extern PMF data_ov003_02238608;

class UnkStruct_0221bec8 {
  public:
    u8 pad_00[0x2b4];
    int idx;
};

extern "C" void func_ov003_0221bec8(UnkStruct_0221bec8 *p)
{
    static PMF tbl[10] = {data_ov003_022385f0, data_ov003_02238590, data_ov003_02238598, data_ov003_022385a0,
                          data_ov003_022385e0, data_ov003_02238600, data_ov003_02238570, data_ov003_02238588,
                          data_ov003_022385a8, data_ov003_02238608};
    if (p->idx < 10) {
        (p->*tbl[p->idx])();
    }
}
