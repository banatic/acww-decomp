/* func_ov096_022a1fa4 @ 0x022a1fa4, 0xe0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_020b9af4(void *p);
extern void func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void func_ov094_0229a2ec(void *p);
extern void func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_ov002_02209b14(void *p);
extern void func_ov002_0220ba24(void *p);
extern void func_0206e388(void *p);
extern void func_ov002_0220b47c(void *p);
extern void func_02066694(void *p);

extern char data_ov096_022a23e8[];

void *func_ov096_022a1fa4(void)
{
    u8 *base;
    u8 *p, *end;

    base = func_ov002_02207f80(0x3028);
    if (base != 0) {
        func_ov002_0220830c();
        *(u32 *) base = (u32) data_ov096_022a23e8;

        p = base + 0x2e8;
        end = base + 0x358;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c(base + 0x0db8);
        func_ov094_0229a2ec(base + 0x0de0);
        func_ov002_02207e40(base + 0x2418);
        func_ov002_02209e44(base + 0x24e8);
        func_ov002_02209ccc(base + 0x2500);
        func_ov002_02209b14(base + 0x2564);
        func_ov002_0220ba24(base + 0x2958);
        func_0206e388(base + 0x2a74);
        func_ov002_0220b47c(base + 0x2d9c);

        *(u32 *) (base + 0x2e20) = 0;
        *(u32 *) (base + 0x2e24) = 0;
        func_02066694(base + 0x2e28);
        func_02066694(base + 0x2f28);
    }
    return base;
}
