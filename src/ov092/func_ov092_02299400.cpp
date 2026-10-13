/* func_ov092_02299400 @ 0x02299400, 0x5c bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02299400;
typedef void (UnkStruct_02299400::*PMF)(void);

struct UnkStruct_02299400 {
    u8 pad_00[0x8c];
    u8 unk_8C;
};

extern PMF data_ov092_022994f0;

extern "C" int func_ov092_02299400(UnkStruct_02299400 *self)
{
    static PMF tbl[1] = {data_ov092_022994f0};

    (self->*tbl[self->unk_8C])();
    return 1;
}
