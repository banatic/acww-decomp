/* room_object_02253058_5: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217d98 @ 0x02217d98, 0x10 bytes, Thumb
 * func_ov004_02217d68 @ 0x02217d68, 0x30 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02217d68;

struct UnkStruct_02217d68_2 {
    char pad_00[0x70];
    void (*unk_70)(struct UnkStruct_02217d68 *, int, int);
};

struct UnkStruct_02217d68 {
    struct UnkStruct_02217d68_2 *v;
};

int func_ov004_02217d98(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x84a) = 0x0;
    return 0x1;
}

void func_ov004_02217d68(struct UnkStruct_02217d68 *self)
{
    if (*(u16 *) ((char *) self + 0x84a) < 0x18) {
        *(u16 *) ((char *) self + 0x84a) = *(u16 *) ((char *) self + 0x84a) + 1;
    }
    if (*(u16 *) ((char *) self + 0x84a) == 0x18) {
        self->v->unk_70(self, 4, 0xff);
    }
}
