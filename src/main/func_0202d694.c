/* func_0202d694 @ 0x0202d694, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
} UnkStruct_0202d694;

extern int func_020644cc(int);
extern void func_02063ccc(void *, u32, int);
extern void func_020638d4(void *, UnkStruct_0202d694 *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern u32 data_020c8eb4[];

void func_0202d694(void *p)
{
    int idx;
    UnkStruct_0202d694 s;
    UnkStruct_0202d694 c;

    idx = func_020644cc(4);
    func_02063ccc(&s, data_020c8eb4[idx], 0);
    c.a = s.a;
    c.b = s.b;
    func_020638d4(p, &c, 0, 0, 1, 1, 0);
    func_02063cc8(&c);
    func_02063cc8(&s);
}
