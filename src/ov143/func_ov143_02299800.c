/* func_ov143_02299800 @ 0x02299800, 0x7e bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    u8 data[0x18];
} Entry;

typedef struct UnkStruct_02299800 {
    u8 pad_00[0x9A];
    short unk_9A;
    u8 pad_9C[4];
    u8 *unk_A0;
} UnkStruct_02299800;

extern void func_ov143_02299880(UnkStruct_02299800 *self, int idx, Entry *p, void *ctx);
extern void func_ov143_022998dc(UnkStruct_02299800 *self, u8 byte, Entry *p, void *ctx);

void func_ov143_02299800(UnkStruct_02299800 *self, Entry *base, void *ctx)
{
    int i;
    Entry *p;

    p = base;
    for (i = 0; i < 8; i++) {
        if (i == self->unk_9A) {
            func_ov143_02299880(self, i, p, ctx);
        } else {
            func_ov143_022998dc(self, self->unk_A0[i], p, ctx);
        }
        p++;
    }

    base = (Entry *) ((char *) base + 0x10);

    for (; i < 16; i++) {
        if (i == self->unk_9A) {
            func_ov143_02299880(self, i, base, (char *) ctx + 0x38);
        } else {
            func_ov143_022998dc(self, self->unk_A0[i], base, (char *) ctx + 0x38);
        }
        base++;
    }
}
