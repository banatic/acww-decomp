/* func_ov004_0222b7e4 @ 0x0222b7e4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_0222b7e4;
extern int func_020310c8(int);
extern void func_02010d28(void *, void *);
void func_ov004_0222b7e4(u8 *self)
{
    int p[3];
    UnkStruct_0222b7e4 *q = (UnkStruct_0222b7e4 *) (self + 0x7d4);
    p[0] = q->a;
    p[1] = func_020310c8(0);
    p[2] = q->b;
    func_02010d28(self, p);
}
