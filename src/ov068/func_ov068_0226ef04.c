/* func_ov068_0226ef04 @ 0x0226ef04, 0xf8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov003_02236128(void *self);
extern void func_0204f7e0(void *a, void *b);
extern int FX_Div(int a, int b);
extern void *func_020b03f8(int arg);
extern void func_020044c0(void *ptr, int a, long long b);
typedef struct UnkStruct_0226ef04_2 {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[0x26c - 0x60];
    u32 unk_26C;
} UnkStruct_0226ef04_2;
typedef struct UnkStruct_0226ef04_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x5c - 0xc];
    u32 unk_5C;
    u8 pad_60[0x64 - 0x60];
    u32 unk_64;
    u8 pad_68[0xa8 - 0x68];
    u32 unk_A8;
    u8 pad_AC[0x26c - 0xac];
    u32 unk_26C;
    u8 pad_270[0x314 - 0x270];
    u32 unk_314;
    u32 unk_318;
    u8 pad_31C[0x328 - 0x31c];
    u8 unk_328[0x378 - 0x328];
    u16 unk_378;
    u8 pad_37A[0x37c - 0x37a];
    u32 unk_37C;
    u32 unk_380;
    u32 unk_384;
    u8 pad_388[0x399 - 0x388];
    u8 unk_399;
} UnkStruct_0226ef04_3;
typedef struct UnkStruct_0226ef04 {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
} UnkStruct_0226ef04;
int func_ov068_0226ef04(UnkStruct_0226ef04_3 *self)
{
    UnkStruct_0226ef04_2 *sub;
    int x;
    int y;
    int idx;
    UnkStruct_0226ef04 *p;
    UnkStruct_0226ef04_3 *ptr2;
    ptr2 = self;
    ptr2->unk_378 &= ~0x10;
    ptr2->unk_378 |= 0x20;
    sub = (UnkStruct_0226ef04_2 *) func_ov003_02236128(ptr2);
    func_0204f7e0(&ptr2->unk_37C, &sub->unk_5C);
    x = sub->unk_26C;
    y = ptr2->unk_26C;
    ptr2->unk_380 = ptr2->unk_380 + ((((2 * x) - (x >> 3)) - (y >> 3)) - 0x400);
    ptr2->unk_A8 = -(FX_Div(0, 0x3e8000) + 0x8f2);
    idx = ptr2->unk_08 & 1;
    p = (UnkStruct_0226ef04 *) func_020b03f8(1);
    p[idx & 1].a = 3 * 0;
    p[idx & 1].b = 0;
    p[idx & 1].c = 0;
    p[idx & 1].d = 0x800;
    ptr2->unk_314 = FX_Div(ptr2->unk_37C - ptr2->unk_5C, 0x10000);
    ptr2->unk_318 = FX_Div(ptr2->unk_384 - ptr2->unk_64, 0x10000);
    ptr2->unk_399 = 0;
    func_020044c0(&ptr2->unk_328[0], 0x81e, 0x7f);
    return 1;
}
