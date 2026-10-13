/* func_ov050_02262e90 @ 0x02262e90, 0x5c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov050_02263394(void *a0, void *a1);
extern void func_020984e8(void);
extern int func_02099640(void);
extern void func_0209ad9c(int a, int b);
extern void func_0209b4d4(void);
extern int func_0209bba0(void);

void func_ov050_02262e90(void *a0, void *a1)
{
    if (func_ov050_02263394(a0, a1) != 0) {
        return;
    }
    func_020984e8();
    func_0209ad9c(func_02099640(), 0);
    func_0209b4d4();
    if (func_0209bba0() == 1) {
        ((u8 *) a1)[4] = 0x31;
        return;
    }
    if (((u8 *) *(u8 **) ((u8 *) a0 + 0xb4))[0x73e] == 0) {
        ((u8 *) a1)[4] = 0x2b;
        *(u8 *) (*(u8 **) ((u8 *) a0 + 0xb4) + 0x73e) = 1;
    } else {
        ((u8 *) a1)[4] = 0x10;
    }
}
