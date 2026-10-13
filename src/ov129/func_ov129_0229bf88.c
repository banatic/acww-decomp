/* func_ov129_0229bf88 @ 0x0229bf88, 0x34 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x2f78];
    u16 table[16];
} UnkStruct_0229bf88;

void func_ov129_0229bf88(UnkStruct_0229bf88 *self)
{
    int i;
    u16 *q = self->table;

    for (i = 0; i < 16; i++) {
        u16 v = *q;
        if (v != 0xffff) {
            ((u8 *) self + v)[0x2f98] = 2;
        }
        q++;
    }
}
