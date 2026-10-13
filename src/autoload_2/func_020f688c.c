/* func_020f688c @ 0x020f688c, 0xbc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    u8 unk_14[0x14];
    u8 unk_28[0x11];
    s8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
} UnkStruct_020f688c;

extern void func_020f6580(UnkStruct_020f688c *, int);
extern void func_020f6564(UnkStruct_020f688c *, int);
extern void func_020f7054(void *, u16, void *);

void func_020f688c(UnkStruct_020f688c *self, unsigned int value, void *p3)
{
    unsigned int next;
    self->unk_3C = 1;
    self->unk_39 = -1;
    if (value == 0x190) {
        func_020f7054(&self->unk_14, 0xd3, p3);
        return;
    }
    if (value < 0xc8) {
        next = value + 0x263;
        func_020f6580(self, next);
        next = value + 4;
        func_020f6564(self, next);
        func_020f7054(&self->unk_14, (u16) next, p3);
    } else {
        next = value + 0x231;
        func_020f6580(self, next);
        next = value - 0x2e;
        func_020f6564(self, next);
        func_020f7054(&self->unk_14, (u16) next, p3);
    }
}
