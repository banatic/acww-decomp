/* func_020913f0 @ 0x020913f0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
    u32 c;
    s16 d;
    u16 pad_0E;
    s16 e;
    u16 pad_12;
    u32 id;
    u32 tail;
} Entry;

void func_020913f0(Entry *arr, int id, const u32 *src, const s16 *p1, const s16 *p2)
{
    int i;
    if (id == -1) {
        return;
    }
    for (i = 0; i < 32; i++) {
        Entry *e = &arr[i];
        if (id == e->id) {
            e->a = src[0];
            e->b = src[1];
            e->c = src[2];
            if (p1) {
                e->d = *p1;
            }
            if (p2) {
                e->e = *p2;
            }
        }
    }
}
