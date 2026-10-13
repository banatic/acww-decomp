/* func_ov004_022217fc @ 0x022217fc, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void func_0202e8e4(void *p);
extern void func_ov004_02220d3c(void *p);
extern int data_ov004_02253e10;

void *func_ov004_022217fc(void)
{
    char *o = (char *) func_020edf70(0xaec);
    if (o != 0) {
        func_0202e8e4(o);
        *(int *) o = (int) &data_ov004_02253e10;
        *(u16 *) (o + 0x898) = 0xfff1;
        func_ov004_02220d3c(o + 0x918);
        *(int *) (o + 0xad0) = 0;
        *(int *) (o + 0xad4) = 0;
    }
    return o;
}
