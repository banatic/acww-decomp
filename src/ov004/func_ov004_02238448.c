/* func_ov004_02238448 @ 0x02238448, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238448 {
    u8 pad_00[0x110];
    int left;
    u8 pad_114[0x158 - 0x114];
    int done;
    u8 pad_15C[0x204 - 0x15c];
    int step;
    int total;
    u8 pad_20C[0x20e - 0x20c];
    u8 phase;
};

void func_ov004_02238448(struct UnkStruct_02238448 *self)
{
    int n;

    n = self->total - self->step * self->done;
    if (n <= 0) {
        n = 0;
        self->phase = 4;
        self->done = 0;
    }
    self->left = n;
}
