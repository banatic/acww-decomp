/* func_02041850 @ 0x02041850, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02073d90(int);
extern void func_0204162c(void);
extern void func_02041604(void *receiver);
extern void func_020415e8(void *receiver);
extern void func_020415d0(void *receiver);
extern void func_020414e0(void *receiver);
extern void func_02041470(void *);
extern void func_0204141c(void *receiver);

extern int data_020ccf94;
extern u8 data_021c75a0;

int func_02041850(void *a)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_0204162c();
        switch (data_021c75a0) {
            case 0:
                func_02041604(a);
                break;
            case 1:
                func_020415e8(a);
                break;
            case 2:
                func_020415d0(a);
                break;
            case 3:
                func_020414e0(a);
                break;
            case 4:
                func_02041604(a);
                break;
            case 5:
                func_02041470(a);
                break;
            case 6:
                func_0204141c(a);
                break;
        }
    }
    return 1;
}
