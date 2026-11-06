/* event_announce_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02041850 @ 0x02041850, 0x80 bytes, Thumb
 * func_020417d8 @ 0x020417d8, 0x78 bytes, Thumb
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
extern int func_020412a0(void);
extern int func_0203e340(void);
extern void func_0203e328(void);
extern void func_020417ac(void);
extern int data_021c7590;
extern unsigned char data_021c75a0[3];
extern int data_020db6e0;
extern unsigned char data_021f39c8[10];

int func_02041850(void *a)
{
    if (func_02073d90(data_020ccf94) == 0) {
        func_0204162c();
        switch ((*(u8 *) data_021c75a0)) {
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

int func_020417d8(void)
{
    if (func_020412a0() != 0) {
        return 1;
    }
    if (func_0203e340() != 0) {
        func_0203e328();
        data_021c7590 = 0;
        data_021c75a0[0] = 0;
        data_021c75a0[2] = 0;
    }
    switch (data_021c75a0[0]) {
        case 0:
            if (data_020db6e0 == 0x63) {
                func_020417ac();
            }
            break;
        case 1:
            data_021c75a0[0] = 2;
            break;
        default:
            break;
    }
    if (func_02073d90((int) ((*(void **) &data_020ccf94))) == 0) {
        data_021f39c8[9] = data_020db6e0;
    }
    return 1;
}
