/* func_ov004_0223fa10 @ 0x0223fa10, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209d0a4(void *argument0);
extern void *func_0209d238(void *argument0, unsigned short *argument1);
extern int func_ov004_0223fa80(void);
extern void func_ov004_0223fad0(void *argument0, char *argument1);
extern void *data_ov004_02259a34;

int func_ov004_0223fa10(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223fa80();
    if (v1 != -0x1) {
        *(u8 *) ((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x196) = a1;
        *(int *) ((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x198) = 0x1;
        func_0209d238((void *) ((void *) (self + 0x180)),
                      (unsigned short *) ((unsigned short *) ((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x284)));
        func_0209d0a4((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x288);
        func_ov004_0223fad0(self, (char *) &data_ov004_02259a34 + (0x2d8 * v1));
        *(void **) ((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x18) = 0x0;
        *(void **) ((char *) &data_ov004_02259a34 + (0x2d8 * v1) + 0x1c) = 0x0;
        return 0x1;
    }
    return 0x0;
}
