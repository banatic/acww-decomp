/* func_ov004_0222137c @ 0x0222137c, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_020682e0(int a);
extern void func_ov004_0222152c(void *s);
extern int func_020e8858(void *p);
extern void func_ov004_02221550(void *s, int a);

int func_ov004_0222137c(char *s)
{
    char *p = func_020682e0(0);
    if (p != 0 && *(int *) (p + 4) != 0) {
        return 1;
    }
    if (*(u8 *) (s + 0xadc) == 0x28) {
        func_ov004_0222152c(s);
    }
    *(short *) (s + 0x8c) = 0;
    *(short *) (s + 0x8e) = -0x8000;
    *(short *) (s + 0x90) = 0;
    *(short *) (s + 0x92) = 0;
    *(short *) (s + 0x94) = -0x8000;
    *(short *) (s + 0x96) = 0;
    if (func_020e8858(s + 0xadc) != 0) {
        if (*(u8 *) (s + 0xadc) == 8) {
            *(int *) (s + 0x5c) = 0x10000;
            *(int *) (s + 0x68) = 0x10000;
            *(int *) (s + 0x64) = 0x1f000;
            *(int *) (s + 0x70) = 0x1f000;
        }
        return 1;
    }
    func_ov004_02221550(s, 2);
    return 1;
}
