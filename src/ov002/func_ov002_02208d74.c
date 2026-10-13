/* func_ov002_02208d74 @ 0x02208d74, 0x5a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02208d74 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern void func_ov002_02208dd0(struct UnkStruct_02208d74 *self);
extern int func_ov002_02208a14(struct UnkStruct_02208d74 *self, int bit);
extern void func_02070a04(char *p, int a, int b);

void func_ov002_02208d74(struct UnkStruct_02208d74 *self)
{
    int i;

    func_ov002_02208dd0(self);
    for (i = 0; i < self->unk_1C; i++) {
        if (i == 0 && func_ov002_02208a14(self, 0x20)) {
            func_02070a04((char *) self + 0x28 + i * 0x74, 0, 0);
        } else {
            func_02070a04((char *) self + 0x28 + i * 0x74, 0, 1);
        }
    }
}
