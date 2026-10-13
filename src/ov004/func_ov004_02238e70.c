/* func_ov004_02238e70 @ 0x02238e70, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238e70 {
    u8 pad_00[0x264];
    u8 mode;
    u8 pad_265[3];
    int ticks;
};

extern void func_ov004_02238e08(struct UnkStruct_02238e70 *self);
extern void func_ov004_02238d88(struct UnkStruct_02238e70 *self);
extern void func_ov004_02238d18(struct UnkStruct_02238e70 *self);

void func_ov004_02238e70(struct UnkStruct_02238e70 *self)
{
    switch (self->mode) {
        case 0:
            func_ov004_02238e08(self);
            break;
        case 1:
            func_ov004_02238d88(self);
            break;
        case 2:
            func_ov004_02238d18(self);
            break;
    }
    self->ticks++;
}
