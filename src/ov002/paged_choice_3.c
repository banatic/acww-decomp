/* paged_choice_3: 2 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02209178 @ 0x02209178, 0x24 bytes, Thumb
 * func_ov002_0220914c @ 0x0220914c, 0x2a bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220914c {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 unk_1F;
};

extern void func_0200277c(int);
extern void func_ov002_02208df8(void *);
extern void func_ov002_02208a0c(struct UnkStruct_0220914c *self, int bit);
extern int func_0206fe54(void);

void func_ov002_02209178(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x17) = 0x0;
    if (*(u8 *) (self + 0x16) != 0x0) {
        func_0200277c(*(u8 *) (self + 0x1a));
        *(u8 *) (self + 0x16) = 0x0;
    }
    func_ov002_02208df8(self);
}

void func_ov002_0220914c(struct UnkStruct_0220914c *self, u8 v)
{
    func_ov002_02208a0c(self, 8);
    if (func_0206fe54()) {
        self->unk_1E = 2;
    } else {
        self->unk_1E = 5;
    }
    self->unk_1F = v;
}
