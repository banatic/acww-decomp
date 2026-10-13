/* func_ov100_0229e400 @ 0x0229e400, 0xfc bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov094_0229af40(void *a, int b);
extern void func_ov094_0229bbd8(void *a, int b);
extern void func_ov094_0229a2b0(void *a, int b);
extern void func_ov002_02209e18(void *a);
extern void func_ov002_02209984(void *a, int b, int c, int _x);
extern int func_0206fca4(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_ov100_0229c2b0(void *a, int b);
extern void func_0206fb58(void);
extern const u8 data_021f3a68[];
extern const u8 data_021f3a86[];

void func_ov100_0229e400(void *self)
{
    int ret;
    int i;

    *(u32 *) ((char *) self + 0x28c0) = 0;
    func_ov094_0229af40((char *) self + 0xcc, 1);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    ((u8 *) self)[0x291f] = 0x20;
    func_ov002_02209e18((char *) self + 0x225c);
    ((u8 *) self)[0x291d] = 0;
    ((u8 *) self)[0x2921] = 0;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    ((u8 *) self)[0x2927] = 0;

    ret = func_0206fca4();

    switch (ret) {
        case 29:
        case 30:
            for (i = 0; i < 15; i++) {
                ((u16 *) ((char *) self + 0x28dc))[i] = 0xfff1;
            }
            func_ov100_0229c2b0(self, 0x200);
            break;
        case 31:
            MI_CpuCopy8(data_021f3a68, (char *) self + 0x28dc, 0x1e);
            break;
        case 32:
            MI_CpuCopy8(data_021f3a86, (char *) self + 0x28dc, 0x1e);
            break;
    }

    MI_CpuCopy8((char *) self + 0x28dc, (char *) self + 0x28fa, 0x1e);
    func_0206fb58();
}