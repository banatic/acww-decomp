/* func_ov004_0222b85c @ 0x0222b85c, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_0222b85c;
extern void func_020110a0(void *object, short *values);
void func_ov004_0222b85c(u8 *self, int stateId)
{
    UnkStruct_0222b85c *q = (UnkStruct_0222b85c *) (self + 0x7d4);
    UnkStruct_0222b85c *d = (UnkStruct_0222b85c *) (self + 0x5c);
    d->a = q->a;
    d->c = q->b;
    func_020110a0(self, (short *) (&q->c));
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
}
