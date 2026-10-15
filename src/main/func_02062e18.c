/* func_02062e18 @ 0x02062e18, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02062e18 {
    void *vptr;
    u8 pad_04[10];
    u16 data[10];
};

extern void *func_020a88ec(struct UnkStruct_02062e18 *self);
extern void func_0205195c(struct UnkStruct_02062e18 *self);
extern int data_020de614;

struct Blk {
    u16 v[10];
};

struct UnkStruct_02062e18 *func_02062e18(struct UnkStruct_02062e18 *self, const u16 *src)
{
    u16 *dst;
    int i;

    func_020a88ec(self);
    self->vptr = &data_020de614;
    func_0205195c(self);

    *(struct Blk *) ((u8 *) self + 0xe) = *(struct Blk *) src;

    return self;
}