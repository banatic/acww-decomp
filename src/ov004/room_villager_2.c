/* room_villager_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221e7c4 @ 0x0221e7c4, 0x4c bytes, Thumb
 * func_ov004_0221e780 @ 0x0221e780, 0x44 bytes, Thumb
 */

#include "types.h"

extern int func_0201c2c8(void *p, u8 k);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern u16 data_020c80f8;
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, unsigned short);

int func_ov004_0221e7c4(char *a, char *b)
{
    int r = func_0201c2c8(b, *(u8 *) (b + 0x560));
    func_02019d0c(b + 0x564, 3, 2, 0, 0, 0, r, 0, 0, data_020c80f8, 0);
    *(u8 *) (a + 0xc) = 0;
    return 1;
}

void func_ov004_0221e780(void *a0, char *a1)
{
    if (func_02019e00(a1 + 0x564) == 3) {
        if (func_02019de8(a1 + 0x564) != 0) {
            func_02019c6c(a1 + 0x564, 2, (*(unsigned short *) &data_020c80f8));
            ((unsigned char *) a0)[0xc] = 1;
        }
    }
}
