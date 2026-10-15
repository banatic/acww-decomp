/* func_02028284 @ 0x02028284, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    u32 unk_830;
} UnkStruct_02028284_2;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_02028284_2 *unk_100;
    u8 unk_104[0x122 - 0x104];
    u8 unk_122;
    u8 pad_123[0x160 - 0x123];
    u32 unk_160;
} UnkStruct_02028284_3;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_02028284_4;

typedef struct {
    u32 w;
    u8 b;
} UnkStruct_02028284;

extern int func_0202d9c4(UnkStruct_02028284_3 *self);
extern int func_0209bc40(int x);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0209bb88(int x);
extern int func_0202da38(UnkStruct_02028284_3 *a0, void *a1, void *a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_0209b4cc(u32 x, int y);
extern void func_02015e10(UnkStruct_02028284_3 *self, int r, int idx);
extern int func_0209bb70(int x);
extern void func_02015de4(UnkStruct_02028284_3 *self, int r, int idx, int val);

extern UnkStruct_02028284 data_020c89d8;
extern UnkStruct_02028284 data_020c8a70;

void func_02028284(UnkStruct_02028284_3 *self, UnkStruct_02028284_4 *out)
{
    UnkStruct_02028284 *r4;
    int v, a, b;

    r4 = 0;
    v = func_0209bc40(func_0202d9c4(self));
    switch (v) {
        case 10:
            r4 = &data_020c89d8;
            break;
        case 19:
            r4 = &data_020c8a70;
            break;
    }

    if (r4 != 0) {
        a = func_020036e8(func_0208150c(self->unk_100->unk_830));
        b = func_0209bb88(func_0202d9c4(self));
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, a, r4->w, r4->b, b, 0);

        if (self->unk_160 != 0) {
            func_02015e10(self, func_0209b4cc(self->unk_160, 0), 0);
            func_02015e10(self, func_0209b4cc(self->unk_160, 1), 1);
            func_02015de4(self, func_0209bb70(func_0202d9c4(self)), 0, 7);
        }
    }

    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
}
