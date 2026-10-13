/* func_ov068_022763e4 @ 0x022763e4, 0x72 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020984e8(void *);
extern u8 *func_02099640(void *);
extern void func_0209e234(void *, int);
extern void func_0209e474(void *);
extern int func_0209e3ac(void *, void *, int);
extern void MI_CpuCopy8(void *, void *, u32);

int func_ov068_022763e4(void *arg0)
{
    u32 a[2];
    u32 b[2];
    u32 c[2];

    MI_CpuCopy8(func_02099640(func_020984e8(arg0)) + 0xc0, a, 8);
    MI_CpuCopy8(a, b, 8);
    func_0209e234(b, 0x1e);

    c[0] = 0;
    c[1] = 0;
    func_0209e474(c);

    if (func_0209e3ac(a, c, 0x3e) != -1) {
        if (func_0209e3ac(a, c, 0x3e) != 0) {
            goto fail;
        }
    }

    if (func_0209e3ac(c, b, 0x3e) != -1) {
        goto fail;
    }

    return 1;

fail:
    return 0;
}
