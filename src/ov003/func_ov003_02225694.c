/* func_ov003_02225694 @ 0x02225694, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} UnkStruct_02225694;

extern void func_ov003_022251a4(char *self, char *p, UnkStruct_02225694 m);

char *func_ov003_02225694(char *self, u16 *b, int c, int d, UnkStruct_02225694 m)
{
    char *p;
    u16 v = *b;
    if (v == 0x25) {
        p = self + 0x480 + ((c ^ d) & 1) * 0x3a8;
    } else if (v == 0xc7) {
        p = self + 0x14f4;
    } else {
        p = self + 0xf78;
    }
    func_ov003_022251a4(self, p, m);
    return p;
}
