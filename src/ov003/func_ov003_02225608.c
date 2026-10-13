/* func_ov003_02225608 @ 0x02225608, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} UnkStruct_02225608;

extern void func_ov003_022251a4(char *self, char *p, UnkStruct_02225608 m);

char *func_ov003_02225608(char *self, u16 *b, UnkStruct_02225608 m)
{
    char *p;
    int c;
    u16 v;
    int k;
    c = 0;
    v = *b;
    if (v >= 0x2b && v <= 0x2e) {
        c = 1;
    }
    if (c) {
        k = v - 0x2b;
    } else if (v >= 0xff && v <= 0x102) {
        k = v - 0xff;
    } else if (v >= 0x62 && v <= 0x65) {
        k = v - 0x5e;
    } else {
        k = v - 0xc8;
    }
    p = *(char **) (self + k * 4 + 0x4978);
    func_ov003_022251a4(self, p, m);
    return p;
}
