/* func_ov004_0221c410 @ 0x0221c410, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_ov004_0221e2c0(void);
extern int func_020e8ed8(int dx, int dz);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201ad18(void *p, int a, int b, void *o, void *t, int c, int d, int e);
extern u16 data_020c80f8;
extern int data_021fbee8;
extern int data_020c814c;

int func_ov004_0221c410(char *s)
{
    char *m = s + 0x564;
    char *o = func_ov004_0221e2c0();
    if (o != 0) {
        func_02019d0c(m, 3, 1, 0, 0, 0,
                      func_020e8ed8(*(int *) (o + 0x5c) - *(int *) (s + 0x5c), *(int *) (o + 0x64) - *(int *) (s + 0x64)), 0,
                      0, data_020c80f8, 0);
        func_0201ad18(s + 0x3b0, 2, 0, o, &data_021fbee8, 4, data_020c814c, 1);
        return 1;
    }
    return 0;
}
