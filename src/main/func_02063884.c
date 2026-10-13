/* func_02063884 @ 0x02063884, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x;
    u32 y;
} Pair;

extern void func_020638d4(u32 a, Pair *b, u32 c, u32 d, u32 e, u32 f, u32 g);
extern void func_02063cc8(Pair *b);

void func_02063884(u32 arg0, Pair *arg1)
{
    Pair local;
    local.x = arg1->x;
    local.y = arg1->y;
    func_020638d4(arg0, &local, 0, 0, 1, 0, 0);
    func_02063cc8(&local);
}
