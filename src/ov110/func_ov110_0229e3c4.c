/* func_ov110_0229e3c4 @ 0x0229e3c4, 0xec bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229e3c4 {
    u8 pad_00[0x94];
    u32 unk_94;
    u8 pad_98[0xb0 - 0x98];
    u16 arr1[15];
    u16 arr2[15];
    u8 pad_EC[0xf1 - 0xec];
    u8 unk_F1;
    u8 pad_F2[0xf3 - 0xf2];
    u8 unk_F3;
    u8 pad_F4[0xf5 - 0xf4];
    u8 unk_F5;
    u8 pad_F6[0xfb - 0xf6];
    u8 unk_FB;
    u8 pad_FC[0x138 - 0xfc];
    u32 unk_138;
    u8 pad_13C[0xb98 - 0x13c];
    u32 unk_B98;
    u8 pad_B9C[0xbc0 - 0xb9c];
    u32 unk_BC0;
    u8 pad_BC4[0x22c8 - 0xbc4];
    u32 unk_22C8;
    u8 pad_22CC[0x2344 - 0x22cc];
    u32 unk_2344;
};

extern void func_ov094_0229af40(void *, int);
extern void func_ov094_0229bbd8(void *, int);
extern void func_ov094_0229a2b0(void *, int);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209984(void *, int, int, int _x);
extern int func_0206fca4(void);
extern void func_0206fb58(void);
extern void func_ov110_0229c2b8(struct UnkStruct_0229e3c4 *, unsigned int);
extern void MI_CpuCopy8(void *, const void *, int);
extern unsigned char data_021f3a68[30];
extern unsigned char data_021f3a86[30];

void func_ov110_0229e3c4(struct UnkStruct_0229e3c4 *self)
{
    int v;
    int i;

    self->unk_94 = 0;
    func_ov094_0229af40(&self->unk_138, 1);
    func_ov094_0229bbd8(&self->unk_B98, 2);
    func_ov094_0229a2b0(&self->unk_BC0, 6);
    self->unk_F3 = 0x1f;
    func_ov002_02209e18(&self->unk_22C8);
    self->unk_F1 = 0;
    self->unk_F5 = 0;
    func_ov002_02209984(&self->unk_2344, 3, 1, 0);
    self->unk_FB = 0;

    v = func_0206fca4() - 0x1d;
    switch (v) {
        case 0:
        case 1:
            for (i = 0; i < 15; i++) {
                self->arr1[i] = 0xfff1;
            }
            func_ov110_0229c2b8(self, 0x200);
            break;
        case 2:
            MI_CpuCopy8(data_021f3a68, self->arr1, 30);
            break;
        case 3:
            MI_CpuCopy8(data_021f3a86, self->arr1, 30);
            break;
    }
    MI_CpuCopy8(self->arr1, self->arr2, 30);
    func_0206fb58();
}