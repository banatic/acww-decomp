/* func_ov047_02260be0 @ 0x02260be0, 0xbc bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260be0 {
    char pad_00[0xce];
    u16 unk_CE;
    int unk_D0;
} UnkStruct_02260be0;

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);

void func_ov047_02260be0(UnkStruct_02260be0 *self)
{
    u16 tmp;
    int r;
    unsigned int ok;
    unsigned int hit;

    if (func_0204bcdc(&self->unk_CE) != 0) {
        tmp = 0xfff1;
        r = func_0204bc64(&self->unk_CE);
        ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
    } else {
        ok = (self->unk_CE == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        hit = 0;
        if (self->unk_CE >= 0x450c && self->unk_CE <= 0x45db) {
            hit = 1;
        }
        if (hit != 0) {
            self->unk_D0 = 0x3a;
        } else if (self->unk_CE >= 0x12b0 && self->unk_CE <= 0x12e7) {
            self->unk_D0 = 0x3b;
        } else if (self->unk_CE >= 0x12e8 && self->unk_CE <= 0x131f) {
            self->unk_D0 = 0x3c;
        } else {
            self->unk_D0 = 0x3d;
        }
    }
}
