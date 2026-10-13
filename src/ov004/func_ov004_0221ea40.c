/* func_ov004_0221ea40 @ 0x0221ea40, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov004_0225395c[2];
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern u16 data_020c80f8;

int func_ov004_0221ea40(char *a, char *b)
{
    struct UnkStruct_0221ea40 {
        int a, b;
    };
    *(struct UnkStruct_0221ea40 *) (b + 0x898) = *(struct UnkStruct_0221ea40 *) &data_ov004_0225395c[0];
    func_02019d0c(b + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(int *) (a + 0x10) = 0;
    return 1;
}
