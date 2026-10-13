/* func_ov126_022a1d90 @ 0x022a1d90, 0xfc bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a1d90 UnkStruct_022a1d90;
struct UnkStruct_022a1d90 {
    u8 pad_00[0x94];
    u32 unk_94;
    u32 unk_98;
    u32 unk_9C;
    u32 unk_A0;
    u8 pad_A4[3];
    u8 unk_A7;
    u8 pad_A8[8];
    u32 unk_B0;
    u8 pad_B4[0x19c - 0xb4];
    u8 unk_19C;
    u8 pad_19D[0x3dc4 - 0x19d];
    u8 unk_3DC4;
    u8 pad_3DC5[0x3f90 - 0x3dc5];
    u8 unk_3F90;
};

extern int func_ov126_0229f7c8(UnkStruct_022a1d90 *self, int arg);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov124_0229eeb8(void *p, int a, u32 b);
extern int func_ov002_02207f60(UnkStruct_022a1d90 *self);
extern void func_ov002_0220ad18(void *p, int v);
extern void func_ov095_0229b1c8(void *p, int a, u32 b, int c);
extern void func_ov095_0229ae84(void *p, int a, u32 b);
extern void func_02088df8(int a1, void *a2, u32 a3, u32 a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12);
extern void func_ov095_0229af58(void *p, int a, int b, int c);
extern u8 data_ov126_022a20b0;

int func_ov126_022a1d90(UnkStruct_022a1d90 *self)
{
    u32 v94 = self->unk_94;
    if (!func_ov126_0229f7c8(self, 1)) {
        return 0;
    }

    if (func_0206fe54()) {
        func_ov002_02209eb8(&self->unk_3F90);
    }
    func_ov124_0229eeb8(&self->unk_B0, 0, v94);
    func_ov002_0220ad18(&self->unk_3DC4, func_ov002_02207f60(self));
    func_ov095_0229b1c8(&self->unk_19C, 0x80, v94 + 0x60, 1);
    func_ov095_0229ae84(&self->unk_19C, 0x80, v94 + 0x60);
    if (func_ov126_0229f7c8(self, 0x100)) {
        func_02088df8(1, &data_ov126_022a20b0, self->unk_A0 + 0x80, v94 + 0x60, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    if (func_ov126_0229f7c8(self, 2)) {
        u32 v1 = self->unk_98;
        u32 v2 = self->unk_9C;
        self->unk_A7 = self->unk_A7 + 1;
        if ((self->unk_A7 & 0x10) != 0) {
            func_ov095_0229af58(&self->unk_19C, v1, v2, 2);
        }
    }
    return 1;
}
