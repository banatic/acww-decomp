/* func_ov004_0221e15c @ 0x0221e15c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_0202e1fc(void *);
extern int data_ov004_02253798[2];
extern void func_ov004_0221e080(void *);
extern void func_02013c0c(void *);
int func_ov004_0221e15c(u8 *self)
{
    int a, b;
    if (func_0202e1fc(self) == 0) {
        return 0;
    }
    a = data_ov004_02253798[0];
    b = data_ov004_02253798[1];
    *(int *) (self + 0xa44) = a;
    *(int *) (self + 0xa48) = b;
    func_ov004_0221e080(self);
    func_02013c0c(self + 0x558);
    return 1;
}
