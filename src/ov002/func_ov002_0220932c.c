/* func_ov002_0220932c @ 0x0220932c, 0x6c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220932c {
    u8 pad_00[0x18];
    u8 unk_18;
    u8 pad_19;
    u8 unk_1A;
};

extern int func_02002d8c(int v);
extern void func_ov002_0220851c(char *p, int a, int b, int c, int d);
extern void func_ov002_02209464(struct UnkStruct_0220932c *self);
extern int func_ov002_02208594(char *p, int a);
extern void func_02001a5c(void);
extern void func_ov002_02208a04(struct UnkStruct_0220932c *self, int bit);
extern void func_0200277c(int v);
extern void func_ov002_0220968c(struct UnkStruct_0220932c *self, int v);

void func_ov002_0220932c(struct UnkStruct_0220932c *self)
{
    int t;

    if (self->unk_18 == 0) {
        t = func_02002d8c(self->unk_1A);
        func_ov002_0220851c((char *) self + 0x3b0, t, 3, 0, 0x30);
        func_ov002_02209464(self);
        self->unk_18 = self->unk_18 + 1;
    }
    if (func_ov002_02208594((char *) self + 0x3b0, 0)) {
        func_02001a5c();
        func_ov002_02208a04(self, 1);
        func_0200277c(self->unk_1A);
        func_ov002_0220968c(self, 0);
    } else {
        func_ov002_02209464(self);
    }
}
