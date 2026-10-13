/* func_ov099_0229cf48 @ 0x0229cf48, 0x6c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x225c];
    u32 unk_225C;
    unsigned char pad_2260[0x598];
    u32 unk_27F8;
    u32 unk_27FC;
    unsigned char pad_2800[0x106];
    u8 unk_2906;
} UnkStruct_0229cf48;

extern void func_ov002_02209d68(void *p, u32 a, u32 b);
extern u32 func_ov099_0229cd70(UnkStruct_0229cf48 *self, u8 value);
extern u32 func_ov099_0229cd1c(UnkStruct_0229cf48 *self, u8 value);
extern void func_ov002_02209d38(void *p, u32 b, u32 c, u32 d);
extern void func_ov002_02209d8c(void *p);
extern void func_ov099_0229c8f8(UnkStruct_0229cf48 *self);
extern void func_ov002_02208098(UnkStruct_0229cf48 *self, u32 arg);

void func_ov099_0229cf48(UnkStruct_0229cf48 *self, u8 value, u32 arg2)
{
    u32 val;
    u32 val2;
    self->unk_2906 = value;
    func_ov002_02209d68(&self->unk_225C, self->unk_27F8, self->unk_27FC);
    val = func_ov099_0229cd70(self, value);
    val2 = func_ov099_0229cd1c(self, value);
    func_ov002_02209d38(&self->unk_225C, val, val2, arg2);
    func_ov002_02209d8c(&self->unk_225C);
    func_ov099_0229c8f8(self);
    func_ov002_02208098(self, 0x10);
}
