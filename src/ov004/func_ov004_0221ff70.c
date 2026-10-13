/* func_ov004_0221ff70 @ 0x0221ff70, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void func_0202e8e4(void *p);
extern void func_ov004_0221f860(void *p);
extern int data_ov004_02253bb4;

void *func_ov004_0221ff70(void)
{
    char *o = (char *) func_020edf70(0xa60);
    if (o != 0) {
        func_0202e8e4(o);
        *(int *) o = (int) &data_ov004_02253bb4;
        *(u16 *) (o + 0x898) = 0xfff1;
        *(int *) (o + 0x89c) = 0;
        *(int *) (o + 0x8a0) = 0;
        func_ov004_0221f860(o + 0x8a8);
    }
    return o;
}
