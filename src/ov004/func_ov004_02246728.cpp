/* func_ov004_02246728 @ 0x02246728, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02246728;
typedef void (UnkStruct_02246728::*PMF)(void);

struct UnkStruct_02246728 {
    u8 pad_00[0x50];
    int unk_50;
    int unk_54;
};

extern PMF data_ov004_02256894, data_ov004_0225689c, data_ov004_022568b4, data_ov004_022568a4;
extern "C" int func_020b6760(void);
extern "C" int func_020b6730(void);
extern "C" int func_020b65c4(void);

extern "C" int func_ov004_02246728(UnkStruct_02246728 *self)
{
    self->unk_50 = func_020b6760();
    if (func_020b6730() != 0) {
        self->unk_54 = 0;
    } else if (func_020b65c4() == 0xa) {
        self->unk_54 = 1;
    } else if (func_020b65c4() == 0xf) {
        self->unk_54 = 2;
    } else {
        self->unk_54 = 3;
    }
    {
        static PMF tbl[4] = {data_ov004_02256894, data_ov004_0225689c, data_ov004_022568b4, data_ov004_022568a4};
        (self->*tbl[self->unk_54])();
    }
    return 1;
}
