/* func_ov125_022a012c @ 0x022a012c, 0xe8 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a012c {
    u8 pad_00[0x87b];
    u8 unk_87B;
    u8 unk_87C;
} UnkStruct_022a012c;

typedef struct GlobalReg {
    u16 pad_00;
    u16 flags;
} GlobalReg;

extern volatile GlobalReg data_021fbe40; // placed at 0x021fbe40

extern int func_ov002_02208014(UnkStruct_022a012c *self);
extern int func_ov002_02208008(UnkStruct_022a012c *self);
extern int func_ov125_0229f784(UnkStruct_022a012c *self, int arg);
extern void func_ov125_0229fee4(UnkStruct_022a012c *self);
extern void func_ov125_0229fd04(UnkStruct_022a012c *self);
extern void func_ov125_0229fa80(UnkStruct_022a012c *self);
extern void func_ov125_0229fc90(UnkStruct_022a012c *self);
extern void func_ov125_0229fc24(UnkStruct_022a012c *self);
extern void func_ov125_0229faf8(UnkStruct_022a012c *self);
extern void func_ov002_02207d24(void *addr, int arg);
extern void func_ov002_02207d00(void *addr);
extern void func_ov002_0220a1dc(void *addr);
extern void func_ov002_0220a720(void *addr, int arg);
extern void func_ov002_02208098(UnkStruct_022a012c *self, int arg);

void func_ov125_022a012c(UnkStruct_022a012c *self)
{
    u16 reg;

    if (func_ov002_02208014(self)) {
        func_ov125_0229fee4(self);
        func_ov002_02207d24((char *) self + 0x574, 1);
        return;
    }

    if (func_ov125_0229f784(self, func_ov002_02208008(self))) {
        func_ov125_0229fd04(self);
        func_ov125_0229fa80(self);
        func_ov002_02207d24((char *) self + 0x574, 0);
        return;
    }

    reg = data_021fbe40.flags;

    if (reg & 1) {
        if (self->unk_87C == 8) {
            func_ov002_0220a1dc((char *) self + 0x644);
            func_ov002_02208098(self, 6);
            return;
        } else {
            func_ov002_02207d24((char *) self + 0x574, 1);
            func_ov125_0229fc90(self);
            self->unk_87B = self->unk_87C;
            func_ov125_0229fc24(self);
            func_ov125_0229faf8(self);
            return;
        }
    } else if (reg & 2) {
        func_ov125_0229faf8(self);
        func_ov002_0220a720((char *) self + 0x6a8, 9);
        func_ov002_02208098(self, 10);
        func_ov002_02207d24((char *) self + 0x574, 1);
        return;
    } else {
        func_ov002_02207d00((char *) self + 0x574);
        return;
    }
}
