/* func_020adfc0 @ 0x020adfc0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 tag;
} UnkStruct_020adfc0;

extern void *func_020adfa4(UnkStruct_020adfc0 *a, int i, int v);
extern int func_0204bcdc(void *p);
extern void *func_0204bc64(void *p);
extern int func_020ae02c(UnkStruct_020adfc0 *a, int i);

static __inline int EqA(void *p, void *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

int func_020adfc0(UnkStruct_020adfc0 *a, UnkStruct_020adfc0 *b)
{
    unsigned int i;
    UnkStruct_020adfc0 *p;
    int result;

    for (i = 0; i < 3; i++) {
        p = (UnkStruct_020adfc0 *) func_020adfa4(a, i, 0);
        if (func_0204bcdc(p)) {
            result = EqA(p, b);
        } else {
            result = EqB(p->tag, b->tag);
        }
        if (result != 0) {
            return func_020ae02c(a, i);
        }
    }
    return 0;
}
