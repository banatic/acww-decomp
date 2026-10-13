/* func_02033a24 @ 0x02033a24, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char data[64];
} Entry;

typedef struct {
    Entry entries[40];
    volatile u32 count;
} Container;

extern int func_02033c78(Entry *entry, int a, int b, int c, int d, int e, int f);

int func_02033a24(Container *obj, int a, int b, int c, int d, int e, int f)
{
    if (obj->count < 40) {
        u32 idx = obj->count;
        obj->count = idx + 1;
        return func_02033c78(&obj->entries[idx], a, b, c, d, e, f);
    }
    return 0;
}
