/* func_ov003_02218eac @ 0x02218eac, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02218eac {
    int a;
    int b;
};
void func_ov003_02218eac(u8 *p, struct UnkStruct_02218eac *d)
{
    d->a = p[0];
    d->b = p[1];
}
