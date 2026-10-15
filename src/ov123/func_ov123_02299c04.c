/* func_ov123_02299c04 @ 0x02299c04, 0x9c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02299c04 {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[0x12];
    u8 unk_A0;
    u8 pad_A1[9];
    u8 unk_AA;
};

extern int func_ov123_02299650(void *self, int arg);
extern void func_ov123_02299630(void *self, int arg);
extern int func_ov123_02299d34(void *self);
extern int func_ov123_02299d24(void *self);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov123_02299c04(struct UnkStruct_02299c04 *self)
{
    if ((u8) (self->unk_AA + 0xe3) <= 1) {
        func_ov002_0220a314((u8 *) self + 0x1cc);
    } else {
        func_ov002_0220a2b4((u8 *) self + 0x1cc);
    }

    if (func_ov123_02299650(self, 0x200) != 0) {
        int a = func_ov123_02299d34(self);
        int b = func_ov123_02299d24(self);
        func_ov002_0220a0b4((u8 *) self + 0x1cc, a, b);
        func_ov123_02299630(self, 0x200);
    } else {
        int a = func_ov123_02299d34(self);
        int b = func_ov123_02299d24(self);
        func_ov002_0220a05c((u8 *) self + 0x1cc, a, b, 3, 1);
        self->unk_A0 = self->unk_8D;
        func_ov002_02208098(self, 9);
    }
}
