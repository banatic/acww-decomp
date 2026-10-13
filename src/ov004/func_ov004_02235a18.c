/* func_ov004_02235a18 @ 0x02235a18, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02235a18 {
    u8 pad_00[0x1a8];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
};

struct UnkStruct_02235a18_2 {
    struct UnkStruct_02235a18 *p;
};

extern int func_0200322c(void *a, void *b);

int func_ov004_02235a18(struct UnkStruct_02235a18 *self, struct UnkStruct_02235a18_2 *e)
{
    // DECLS
    int d;
    int a;
    struct UnkStruct_02235a18 *o;
    int y;
    int x;
    // ENDDECLS

    o = e->p;
    a = o->unk_1C0;
    d = (s16) (func_0200322c(&self->unk_1A8, &o->unk_1A8) - 0x4000);
    x = (s16) (self->unk_1C0 - d);
    y = (s16) (a - d);
    if (x * y < 0) {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 0x40;
        }
        return 0x80;
    } else if (x < 0) {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 8;
        }
        return 0x10;
    } else {
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        if ((x - 0x4000) * (y - 0x4000) < 0) {
            return 2;
        }
        return 4;
    }
}
