/* func_0209d180 @ 0x0209d180, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Elem {
    u8 pad_00[0x1c];
} Elem;

typedef struct UnkStruct_0209d180 {
    int unk_00;
    u32 count;
    int unk_08;
    Elem *buf;
    int (*fn)(int, int);
    int unk_14;
} UnkStruct_0209d180;

extern void *func_020e98b4(int size);
extern Elem *func_0209d328(Elem *e);
extern int func_0209d2dc(Elem *e, int a, int b, int c, int d);

int func_0209d180(UnkStruct_0209d180 *self, u32 n, int a, int b, int c, int (*fn)(int, int), int f14)
{
    Elem *p;
    u32 i;
    int t;
    int sz;

    self->fn = fn;
    self->unk_14 = f14;
    sz = n * ((c + 0x5b) & ~3);
    self->count = n;
    t = 0;
    self->unk_08 = 0;
    if (c != 0) {
        t = self->fn(sz, 0);
    }
    self->buf = (Elem *) func_020e98b4(0x1c * self->count);
    p = self->buf;
    if (p != 0) {
        for (i = 0; i < self->count; i++) {
            if (p != 0) {
                p = func_0209d328(p);
            }
            if (func_0209d2dc(p, a, b, c, t) == 0) {
                return 0;
            }
            p++;
        }
    }
    return 1;
}
