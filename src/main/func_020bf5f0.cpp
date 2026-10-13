/* func_020bf5f0 @ 0x020bf5f0, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020bf5f0;
typedef void (UnkStruct_020bf5f0::*PMF)(void);

struct UnkStruct_020bf5f0 {
    int idx;
};

extern u32 data_021f6cc8;
extern PMF data_021f6d98[13];
extern PMF data_020e5ca0, data_020e5d20, data_020e5a60, data_020e5c88, data_020e5c80, data_020e5c78, data_020e5c70,
    data_020e59b8, data_020e5c60, data_020e5a90, data_020e5c50, data_020e5c48, data_020e5c40;

extern "C" void func_020bf5f0(UnkStruct_020bf5f0 *p)
{
    PMF f;

    if (!(data_021f6cc8 & 1)) {
        data_021f6d98[0] = data_020e5ca0;
        data_021f6d98[1] = data_020e5d20;
        data_021f6d98[2] = data_020e5a60;
        data_021f6d98[3] = data_020e5c88;
        data_021f6d98[4] = data_020e5c80;
        data_021f6d98[5] = data_020e5c78;
        data_021f6d98[6] = data_020e5c70;
        data_021f6d98[7] = data_020e59b8;
        data_021f6d98[8] = data_020e5c60;
        data_021f6d98[9] = data_020e5a90;
        data_021f6d98[10] = data_020e5c50;
        data_021f6d98[11] = data_020e5c48;
        data_021f6d98[12] = data_020e5c40;
        data_021f6cc8 |= 1;
    }
    f = data_021f6d98[p->idx];
    if (f) {
        (p->*f)();
    }
}
