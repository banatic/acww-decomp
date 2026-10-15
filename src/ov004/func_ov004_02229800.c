/* func_ov004_02229800 @ 0x02229800, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02229800 {
    u8 pad_00[0x141];
    u8 alt;
    u8 pad_142[0x2d0 - 0x142];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
};

extern int func_02056f94(void *p);
extern int func_02008258(struct UnkStruct_02229800 *self, int a);
extern int func_0200d4e8(struct UnkStruct_02229800 *self, int a, int b, int c);
extern int func_ov004_0222a23c(struct UnkStruct_02229800 *self, int a, int b, int c, int d);

void func_ov004_02229800(struct UnkStruct_02229800 *self)
{
    if (func_02056f94(&self->sub)) {
        self->handle = func_02008258(self, self->src);
        if (self->alt) {
            func_ov004_0222a23c(self, 1, 0, 5, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}
