/* func_ov009_02264398 @ 0x02264398, 0x5c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Elem {
    u8 pad_00[0x4c];
    u32 unk_4C;
} Elem;

typedef struct UnkStruct_02264398 {
    u8 pad_00[0x288];
    void *unk_288;
    Elem *base;
    u8 count;
} UnkStruct_02264398;

extern void func_02032658(void *);

void func_ov009_02264398(UnkStruct_02264398 *self)
{
    Elem *p;
    Elem *end;

    if (self->unk_288 != 0) {
        self->unk_288 = 0;
    }

    p = self->base;
    if (p != 0) {
        while (p < (Elem *) ((char *) self->base + self->count * 0x54)) {
            func_02032658(p);
            p->unk_4C = 0;
            p = (Elem *) ((char *) p + 0xa8);
        }
        self->base = 0;
    }

    self->count = 0;
}
