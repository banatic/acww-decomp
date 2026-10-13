/* func_0200a02c @ 0x0200a02c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200a02c {
    u8 pad_00[0x98];
    u32 unk_98;
    u8 pad_9C[0x7fc - 0x9c];
    u32 unk_7FC;
    u32 unk_800;
} UnkStruct_0200a02c;

extern void *data_020ccf94;
extern int func_02073908(void *a, u32 b);
extern void func_02009fac(UnkStruct_0200a02c *self, int a, int b);
extern void func_0200c3b0(UnkStruct_0200a02c *self, int a, int b, int c);

void func_0200a02c(UnkStruct_0200a02c *self)
{
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        if (self->unk_98 == 0) {
            func_02009fac(self, 6, -1);
        }
    } else {
        self->unk_7FC = 0;
        if (self->unk_98 == 0) {
            func_0200c3b0(self, 3, 5, -1);
        }
    }
}
