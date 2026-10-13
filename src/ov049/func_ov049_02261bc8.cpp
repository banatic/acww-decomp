/* func_ov049_02261bc8 @ 0x02261bc8, 0xe8 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_02261bc8;
typedef void (UnkStruct_02261bc8::*PMF)(void);

struct UnkStruct_02261bc8 {
    u8 pad_00[0x1e];
    u8 unk_1E;
};

struct Entry {
    int key;
    PMF fn;
};

extern PMF data_ov049_02263178, data_ov049_022631a0, data_ov049_022631b0, data_ov049_022631c0, data_ov049_02263220,
    data_ov049_02263258, data_ov049_02263108, data_ov049_02263100, data_ov049_022630f8;

extern "C" void func_ov049_02261bc8(UnkStruct_02261bc8 *self)
{
    static Entry tbl[9] = {
        {0xe, data_ov049_02263178},  {0x11, data_ov049_022631a0}, {0x12, data_ov049_022631b0},
        {0x14, data_ov049_022631c0}, {0x1e, data_ov049_02263220}, {0x28, data_ov049_02263258},
        {0x36, data_ov049_02263108}, {0x26, data_ov049_02263100}, {0x23, data_ov049_022630f8},
    };
    unsigned int i = 0;
    u8 *pk = &self->unk_1E;
    while (i < 9) {
        int k = tbl[i].key;
        if (k == *pk) {
            (self->*tbl[i].fn)();
        }
        i++;
    }
}
