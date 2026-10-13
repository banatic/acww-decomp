/* func_ov050_0226491c @ 0x0226491c, 0x58 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 pad_00;
    u32 pad_04;
    u32 unk_08;
} UnkStruct_0226491c;

extern int func_ov050_022604bc(void *self);
extern int data_ov050_02265848[5];

int func_ov050_0226491c(UnkStruct_0226491c *self)
{
    int result = 0;
    if (func_ov050_022604bc(self)) {
        result = 4;
    } else {
        switch (self->unk_08 - 0xd019) {
            case 0:
                result = 0;
                break;
            case 1:
                result = 1;
                break;
            case 2:
                result = 2;
                break;
            case 3:
                result = 3;
                break;
        }
    }
    return data_ov050_02265848[result];
}
