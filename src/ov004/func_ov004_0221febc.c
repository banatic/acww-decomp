/* func_ov004_0221febc @ 0x0221febc, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202e1fc(void *s);
extern void func_ov004_0223d33c(void);
extern void func_02013c0c(void *p);
extern int func_020b65b8(void);
extern int func_020b6654(int);
extern void func_ov004_0221fdf4(void *s, int a);
extern int func_02030864(int a);
extern int func_0201c444(void *s);
extern int func_0204d624(void *p, int a, int b);
extern int data_021fbe94;

int func_ov004_0221febc(char *s)
{
    if (func_0202e1fc(s) == 0) {
        return 0;
    }
    func_ov004_0223d33c();
    *(u16 *) (s + 0x898) = 0xfff1;
    func_02013c0c(s + 0x558);
    if (func_020b6654((int) func_020b65b8()) != 0) {
        func_ov004_0221fdf4(s, 4);
    } else {
        func_ov004_0221fdf4(s, 0);
    }
    func_02030864(0);
    *(int *) (s + 0xa5c) = 0;
    *(int *) (s + 0xa58) = func_0204d624(s + 0xa5c, func_0201c444(s), data_021fbe94);
    return 1;
}
