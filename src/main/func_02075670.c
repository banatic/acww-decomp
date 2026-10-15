/* func_02075670 @ 0x02075670, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b65c4(void);
extern void *func_020a1350(void);
extern int func_020a00fc(void *p);
extern void *func_020a1338(void);
extern void func_020a003c(void *p, int a);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void func_02075670(unsigned char *payload, unsigned int length, int player)
{
    u32 local;
    void *base;
    u32 ret;
    u32 limit;

    if (func_020b65c4() != 0xc) {
        return;
    }

    MI_CpuCopy8(payload, &local, 4);

    base = func_020a1350();

    MI_CpuCopy8(payload + 4, (u8 *) base + local, length - 4);

    ret = (u32) func_020a00fc(base);

    if (ret == 0) {
        limit = 0x17400;
    } else {
        limit = ret + 4;
    }

    if (local + (length - 4) < limit) {
        return;
    }

    func_020a003c(func_020a1338(), 0);
}
