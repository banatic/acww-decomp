/* func_ov114_0229c924 @ 0x0229c924, 0xb8 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_0204c6b8(u32);
extern u8 *func_ov094_0229b088(u8 *, u32);
extern int func_ov114_0229cdcc(u8 *);
extern void MI_CpuCopy8(const void *, void *, u32);
extern void func_020b9a18(void *, void *, void *, int, u32, u32, u32, u32);
extern u32 func_ov094_0229b03c(u8 *, u32);

void func_ov114_0229c924(u8 *self, u32 arg1, int idx)
{
    struct {
        u32 unk0;
        unsigned int v : 10;
        unsigned int pad10_11 : 2;
        unsigned int code : 4;
        unsigned int pad16_31 : 16;
        u32 field8;
    } *e = (void *) (self + 0x1000 + idx * 0xc);
    u32 id = func_0204c6b8(arg1);

    if (id != e->field8) {
        u32 v;
        u8 *src;
        int slot;
        u8 *destA;
        u8 *destB;
        u32 args[4];

        e->field8 = id;
        v = e->v;
        src = func_ov094_0229b088(self, id);
        slot = func_ov114_0229cdcc(self);
        destA = self + 0x988 + (slot << 7);
        destB = destA + 0x40;
        MI_CpuCopy8(src, destA, 0x40);
        MI_CpuCopy8(src + 0x400, destB, 0x40);
        args[0] = v;
        args[1] = v + 1;
        args[2] = v + 0x20;
        args[3] = v + 0x21;
        func_020b9a18(self + 0xe08 + slot * 0x38, destA, destB, 8, args[0], args[1], args[2], args[3]);
        e->code = func_ov094_0229b03c(self, id);
    }
}
