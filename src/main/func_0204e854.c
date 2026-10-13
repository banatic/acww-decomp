/* func_0204e854 @ 0x0204e854, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Same as func_0204e77c: both grid counters live in one struct whose address is taken.
typedef struct UnkStruct_0204e854 {
    int i;
    int j;
} UnkStruct_0204e854;

extern u16 *func_0204ea00(void *a, int *pi);

int func_0204e854(void *a)
{
    int n;
    UnkStruct_0204e854 s;
    u16 *p;
    int k;
    int count;
    int result;

    count = 0;
    s.i = 0;
    s.j = 0;
    result = 0;
    for (s.j = 0, n = 0; s.j < 6; s.j++) {
        for (s.i = 0; s.i < 6; s.i++) {
            p = func_0204ea00(a, &s.i);
            if (p != 0) {
                // do/while: the loop has no entry check.
                k = n;
                do {
                    if (*p == 0x500a) {
                        count++;
                    }
                    p++;
                    k++;
                } while (k < 256);
            }
        }
    }
    if (count >= 9) {
        result = 1;
    }
    return result;
}
