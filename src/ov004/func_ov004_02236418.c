/* func_ov004_02236418 @ 0x02236418, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02236418;
struct UnkStruct_02236418_2 {
    int a, b, c;
};

extern int func_ov004_02236464(struct UnkStruct_02236418 *self, struct UnkStruct_02236418_2 *f);
extern void func_ov004_0223635c(struct UnkStruct_02236418 *self, struct UnkStruct_02236418_2 *f);

struct UnkStruct_02236418 {
    u8 pad_00[0x1ee];
    u8 unk_1EE;
    u8 pad_1EF[0x253 - 0x1ef];
    u8 unk_253;
};

int func_ov004_02236418(struct UnkStruct_02236418 *self)
{
    int ok;
    struct UnkStruct_02236418_2 f;

    ok = 0;
    if (self->unk_253 != 0) {
        if (self->unk_1EE != 1) {
            self->unk_253 = 0;
        }
        return 0;
    }
    if (func_ov004_02236464(self, &f) != 0) {
        func_ov004_0223635c(self, &f);
        ok = 1;
        self->unk_253 = 1;
    }
    return ok;
}
