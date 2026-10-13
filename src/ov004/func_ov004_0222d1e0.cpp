/* func_ov004_0222d1e0 @ 0x0222d1e0, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222d1e0;
typedef int (UnkStruct_0222d1e0::*PMF)(void);

struct UnkStruct_0222d1e0 {
    u8 pad_00[0x24c];
    u8 unk_24C;
};

extern PMF data_ov004_02254d84, data_ov004_02254d8c, data_ov004_02254db4, data_ov004_02254da4;

extern "C" int func_ov004_0222d1e0(UnkStruct_0222d1e0 *self, unsigned int i)
{
    static PMF tbl[4] = {data_ov004_02254d84, data_ov004_02254d8c, data_ov004_02254db4, data_ov004_02254da4};
    if (i < 4) {
        if ((self->*tbl[i])() != 0) {
            self->unk_24C = i;
            return 1;
        }
        return 0;
    }
    return 0;
}
