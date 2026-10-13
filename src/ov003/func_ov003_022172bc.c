/* func_ov003_022172bc @ 0x022172bc, 0x8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022172bc {
    int a;
    int b;
    u8 c;
};
void func_ov003_022172bc(struct UnkStruct_022172bc *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = (u8) c;
}
