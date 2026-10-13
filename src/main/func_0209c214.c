/* func_0209c214 @ 0x0209c214, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209c330(void *p);
extern int func_0209c2c0(void *p);
extern void func_0209c32c(void *p, int n);
extern void func_0209e474(void *p);
extern void MI_CpuCopy8(void *dst, void *src, int n);

void func_0209c214(void *p)
{
    if (func_0209c330(p) == 2 || func_0209c2c0(p) != 0) {
        *((u8 *) p + 0x21) = (*((u8 *) p + 0x21) & ~1) | 1;
    } else {
        *((u8 *) p + 0x21) &= ~1;
    }
    func_0209c32c(p, 0xb);
    func_0209e474(p);
    MI_CpuCopy8(p, (u8 *) p + 8, 8);
}
