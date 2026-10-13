/* func_020516b8 @ 0x020516b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 value;
    u16 pad;
} Entry;
typedef struct {
    u32 *countptr;
    Entry *data;
} HighTable;
typedef struct {
    u32 *lowcount;
    Entry *lowdata;
    u32 pad;
    HighTable *high;
} UnkStruct_020516b8;
int func_020516b8(UnkStruct_020516b8 *p, int key)
{
    u32 i = 0;
    int result = -1;
    u32 count;
    count = *p->lowcount;
    while (i < (*p->lowcount)) {
        int value = result;
        if (i & 0x80000000) {
            HighTable *h = p->high;
            u32 idx = i & 0x7fffffff;
            if (idx < (*h->countptr)) {
                value = h->data[idx].value;
            }
        } else if (i < (*p->lowcount)) {
            value = p->lowdata[i].value;
        }
        if (value == key) {
            result = i;
            break;
        }
        i++;
    }

    return result;
}
