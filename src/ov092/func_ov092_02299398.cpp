/* func_ov092_02299398 @ 0x02299398, 0x68 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02299398;
typedef void (UnkStruct_02299398::*PMF)(void);

struct UnkStruct_02299398 {
    u8 pad_00[0x8d];
    u8 unk_8D;
};

extern PMF data_ov092_022994e8, data_ov092_022994f8;

extern "C" int func_ov092_02299398(UnkStruct_02299398 *self)
{
    static PMF tbl[2] = {data_ov092_022994e8, data_ov092_022994f8};

    (self->*tbl[self->unk_8D])();
    return 1;
}
