/* func_ov102_0229d54c @ 0x0229d54c, 0x9c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x225c];
    u8 unk_225C[0x284];
    u32 unk_24E0;
    u32 unk_24E4;
    u8 pad_24E8[0xba];
    u8 unk_25A2;
} UnkStruct_0229d54c;

extern void func_ov002_02209d68(void *, u32, u32);
extern void func_ov002_02209d38(void *, u32, u32, u32);
extern void func_ov002_02209d8c(void *);
extern int func_ov102_0229d178(UnkStruct_0229d54c *, int);
extern int func_ov102_0229d444(UnkStruct_0229d54c *, int);
extern int func_ov102_0229d1e8(UnkStruct_0229d54c *, int);
extern void func_ov102_0229cd08(UnkStruct_0229d54c *);
extern void func_ov102_0229c298(UnkStruct_0229d54c *, u32);
extern void func_ov102_0229c288(UnkStruct_0229d54c *, u32);
extern void func_ov002_02208098(UnkStruct_0229d54c *, int);

void func_ov102_0229d54c(UnkStruct_0229d54c *self, int a1, int a2)
{
    int v;
    int ret;

    self->unk_25A2 = a1;
    func_ov002_02209d68(&self->unk_225C, self->unk_24E0, self->unk_24E4);
    v = func_ov102_0229d178(self, a1);
    if (func_ov102_0229d444(self, a1) != 0) {
        v -= 8;
    }
    ret = func_ov102_0229d1e8(self, a1);
    func_ov002_02209d38(&self->unk_225C, ret, v, a2);
    func_ov002_02209d8c(&self->unk_225C);
    func_ov102_0229cd08(self);
    if (func_ov102_0229d444(self, a1) != 0) {
        func_ov102_0229c298(self, 0x200);
    } else {
        func_ov102_0229c288(self, 0x200);
    }
    func_ov002_02208098(self, 13);
}
