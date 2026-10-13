/* func_ov004_02227f00 @ 0x02227f00, 0x6 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Rec {
    int id;
    u16 count;
};

void func_ov004_02227f00(struct Rec *r, int id, u16 count)
{
    r->id = id;
    r->count = count;
}
