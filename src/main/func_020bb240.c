/* func_020bb240 @ 0x020bb240, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x1520];
    u32 flag;
    char pad_1524[0x158c - 0x1520 - 4];
    u32 mode;
} UnkStruct_020bb240;

extern void func_020bb35c(UnkStruct_020bb240 *self);
extern void func_020bb30c(UnkStruct_020bb240 *self);
extern void func_020bb2ec(UnkStruct_020bb240 *self);
extern void func_020bb290(UnkStruct_020bb240 *self);

void func_020bb240(UnkStruct_020bb240 *self)
{
    if (self->flag == 0) {
        return;
    }
    switch (self->mode) {
        case 1:
            func_020bb35c(self);
            break;
        case 2:
            func_020bb30c(self);
            break;
        case 3:
            func_020bb2ec(self);
            break;
        case 4:
            func_020bb290(self);
            break;
        case 0:
            break;
    }
}
