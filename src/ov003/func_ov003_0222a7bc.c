/* func_ov003_0222a7bc @ 0x0222a7bc, 0xd0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov003_0222a7bc(char *self, int v, int kind)
{
    s16 *a = (s16 *) (self + 0x96);
    s16 *b = (s16 *) (self + 0x98);
    s16 *c = (s16 *) (self + 0x9a);
    switch (kind) {
        case 0xa:
        case 0xb:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
            *c = *c + 0x7fff;
            *b = -v;
            *a = *a + 0x4000;
            break;
        case 0xf:
            *c = *c + 0x6000;
            *b = v;
            *a = *a + 0x4000;
            break;
        case 0x23:
        case 0x24:
        case 0x25:
            *b = v;
            break;
        case 0x35:
        case 0x36:
            *a = *a + 0x4000;
            *b = v;
            break;
        default:
            *c = *c + 0x4000;
            *a = v;
            *a = *a + 0x4000;
            break;
    }
}
