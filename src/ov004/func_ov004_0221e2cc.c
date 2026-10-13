/* func_ov004_0221e2cc @ 0x0221e2cc, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020edf70(int);
extern void func_0202e8e4(void *);
extern void func_0202decc(void *);
extern int data_ov004_02253868;
extern int data_ov004_022537d8;
void *func_ov004_0221e2cc(void)
{
    u8 *p;
    p = (u8 *) func_020edf70(0xa6c);
    if (p != 0) {
        func_0202e8e4(p);
        *(int **) p = &data_ov004_02253868;
        func_0202decc(p + 0x89c);
        *(int **) (p + 0x89c) = &data_ov004_022537d8;
    }
    return p;
}
