/* func_020bb3a4 @ 0x020bb3a4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x1520];
    u32 flag;
    char pad_1524[0x158c - 0x1520 - 4];
    u32 mode;
} UnkStruct_020bb3a4;

extern void func_020bb568(UnkStruct_020bb3a4 *self);
extern void func_020bb4e0(UnkStruct_020bb3a4 *self);
extern void func_020bb480(UnkStruct_020bb3a4 *self);
extern void func_020bb3f4(UnkStruct_020bb3a4 *self);

void func_020bb3a4(UnkStruct_020bb3a4 *self)
{
    if (self->flag == 0) {
        return;
    }
    switch (self->mode) {
        case 1:
            func_020bb568(self);
            break;
        case 2:
            func_020bb4e0(self);
            break;
        case 3:
            func_020bb480(self);
            break;
        case 4:
            func_020bb3f4(self);
            break;
        case 0:
            break;
    }
}
