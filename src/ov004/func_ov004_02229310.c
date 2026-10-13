/* func_ov004_02229310 @ 0x02229310, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} UnkStruct_02229310;

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int n);
extern u8 data_020e54a8;
extern void func_ov004_0223a704(UnkStruct_02229310 *t);

void func_ov004_02229310(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 0xc)) {
        int on = (data_020e54a8 == 1);
        if (on) {
            const int *q = (const int *) (self + 0x7d4);
            int c = q[1], b = *(int *) (self + 0x60), a = q[0];
            UnkStruct_02229310 t;
            t.a = a;
            t.b = b;
            t.c = c;
            func_ov004_0223a704(&t);
        }
    }
}
