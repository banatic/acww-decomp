/* func_ov105_0229f760 @ 0x0229f760, 0xfc bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void *self);
extern void *data_ov105_0229fad0;
extern void func_02066694(void *p);
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
extern void func_02066688(void);
extern void __cxa_vec_ctor(void *p, int a, int b, void *fn1, void *fn2);
extern void func_ov002_0220b008(void *p);

void *func_ov105_0229f760(void)
{
    u8 *self;
    u8 *p;
    u8 *end;

    self = (u8 *) func_ov002_02207f80(0x6184);
    if (self != 0) {
        func_ov002_0220830c(self);
        *(void **) self = &data_ov105_0229fad0;

        func_02066694(self + 0xb4);
        func_02066694(self + 0x1b4);

        p = self + 0x2c4;
        end = self + 0x2fc;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c(self + 0xd5c);
        func_ov094_0229a2ec(self + 0xd84);
        func_ov002_02207e40(self + 0x23bc);
        func_ov002_02209e44(self + 0x248c);
        func_ov002_02209ccc(self + 0x24a4);
        func_ov002_02209b14(self + 0x2508);
        func_ov002_0220ba24(self + 0x28fc);
        func_0206e388(self + 0x2a18);
        func_ov002_0220b47c(self + 0x2d40);

        __cxa_vec_ctor(self + 0x2db8, 0x32, 0x100, (void *) func_02066694, (void *) func_02066688);

        func_ov002_0220b008(self + 0x5fb8);
    }

    return self;
}
