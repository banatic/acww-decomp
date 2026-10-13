/* func_ov004_0221d4f4 @ 0x0221d4f4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void func_0202e8e4(void *p);
extern void func_0202decc(void *p);
extern int data_ov004_02253674;
extern int data_ov004_022535e4;

void *func_ov004_0221d4f4(void)
{
    char *o = (char *) func_020edf70(0xa70);
    if (o != 0) {
        func_0202e8e4(o);
        *(int *) o = (int) &data_ov004_02253674;
        func_0202decc(o + 0x8a0);
        *(int *) (o + 0x8a0) = (int) &data_ov004_022535e4;
        *(u16 *) (o + 0xa50) = 0xfff1;
    }
    return o;
}
