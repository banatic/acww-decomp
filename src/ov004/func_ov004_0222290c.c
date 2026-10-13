/* func_ov004_0222290c @ 0x0222290c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_0202e1fc(void *);
extern int data_ov004_022540a8[2];
extern void func_ov004_02222820(void *);
extern void func_02013c0c(void *);
int func_ov004_0222290c(u8 *self)
{
    int a, b;
    if (func_0202e1fc(self) == 0) {
        return 0;
    }
    a = data_ov004_022540a8[0];
    b = data_ov004_022540a8[1];
    *(int *) (self + 0xa4c) = a;
    *(int *) (self + 0xa50) = b;
    func_ov004_02222820(self);
    func_02013c0c(self + 0x558);
    return 1;
}
