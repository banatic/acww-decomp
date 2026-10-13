/* func_0206c1cc @ 0x0206c1cc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_0206d56c(void *buf, int arg1, u8 flag);

typedef struct {
    u8 pad_00[0x400];
    u32 base;
    void *arr2[3];
    u32 count;
    u8 pad_414[0x18];
    u32 arr1[3];
    u8 pad_438[3];
    u8 flag;
    u8 buf[1];
} UnkStruct_0206c1cc;

void func_0206c1cc(UnkStruct_0206c1cc *self, int arg1)
{
    u32 c;
    if (self->count >= 3) {
        return;
    }
    self->arr1[self->count] = func_0206d56c(self->buf, arg1, self->flag);
    c = self->count;
    self->count = c + 1;
    self->arr2[c] = (void *) ((u8 *) self + self->base);
}
