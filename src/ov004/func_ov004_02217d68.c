/* func_ov004_02217d68 @ 0x02217d68, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
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
void func_ov004_02217d68(struct UnkStruct_02217d68 *self)
{
    if (*(u16 *) ((char *) self + 0x84a) < 0x18) {
        *(u16 *) ((char *) self + 0x84a) = *(u16 *) ((char *) self + 0x84a) + 1;
    }
    if (*(u16 *) ((char *) self + 0x84a) == 0x18) {
        self->v->unk_70(self, 4, 0xff);
    }
}
