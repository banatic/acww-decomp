/* func_0204e77c @ 0x0204e77c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Both loop counters live in one struct whose address is taken.
typedef struct UnkStruct_0204e77c {
    int i;
    int j;
} UnkStruct_0204e77c;

extern int func_0204ea00(u8 *a, int *pi);
extern int func_0204d7f8(int r, int z, int v, int b);

void func_0204e77c(u8 *a, int b)
{
    UnkStruct_0204e77c s;
    int r;

    s.i = 0;
    s.j = 0;
    for (s.j = 0; s.j < 6; s.j++) {
        for (s.i = 0; s.i < 6; s.i++) {
            r = func_0204ea00(a, &s.i);
            if (r != 0) {
                func_0204d7f8(r, 0, (a + s.j * 6)[s.i] & 0xfff, b);
            }
        }
    }
}
