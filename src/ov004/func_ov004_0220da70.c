/* func_ov004_0220da70 @ 0x0220da70, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct List {
    u32 count;
    void *ent[4];
};

int func_ov004_0220da70(struct List *self, void *p)
{
    u32 i;
    u32 n;

    if (p == 0) {
        return 0;
    }
    n = self->count;
    if (n >= 4) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (self->ent[i] == p) {
            return 0;
        }
    }
    self->count++;
    self->ent[n] = p;
    return 1;
}
