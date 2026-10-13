/* func_ov004_0221ca04 @ 0x0221ca04, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f43e8;
extern void func_02068484(int h, u8 *p, int k);
extern void func_0206844c(int h, u8 *p, int k);
extern void func_ov004_0221c844(int h, int a);
extern int func_020644cc(int);
extern void func_020154b4(void *s, void *p, int a, int b, int c);
extern void func_0209a000(void *p, int a);
extern void func_ov004_0221cfe0(void *s);

void func_ov004_0221ca04(char *s)
{
    u8 buf[4];
    switch (*(u8 *) (s + 0x1e)) {
        case 4:
        case 5:
        case 6:
            break;
        case 7:
        case 8:
            buf[0] = data_021f43e8;
            func_02068484(*(int *) (s + 0x40), &buf[0], 0);
            break;
        case 9:
        case 10:
            func_ov004_0221c844(*(int *) (s + 0x1a4), 0xa);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            buf[1] = (u8) (func_020644cc(2) + 0xf);
            func_0206844c(*(int *) (*(int *) (s + 0x1a4) + 0x8e0), &buf[1], 0);
            break;
        case 15:
        case 16:
            func_020154b4(s, (char *) *(int *) (s + 0x1a4) + 0xa50, 0, 5, 0);
            func_0209a000((char *) *(int *) (s + 0x1a4) + 0xa50, 0);
            func_ov004_0221c844(*(int *) (s + 0x1a4), 0xd);
            break;
        case 17:
        case 18:
            func_ov004_0221cfe0(s);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
            buf[2] = data_021f43e8;
            func_02068484(*(int *) (s + 0x40), &buf[2], 0);
            break;
    }
}
