/* func_ov003_02225404 @ 0x02225404, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} UnkStruct_02225404;

extern void func_ov003_022251a4(char *a, char *p, UnkStruct_02225404 m);

char *func_ov003_02225404(char *a, u16 *b, UnkStruct_02225404 m)
{
    char *p;
    int k;
    int c;
    u16 v;
    c = 0;
    v = *b;
    if (v >= 0x1f && v <= 0x20) {
        c = 1;
    }
    if (c) {
        k = 4;
    } else {
        k = v - 0x21;
    }
    p = a + 0x43e8 + k * 0x9c;
    func_ov003_022251a4(a, p, m);
    return p;
}
