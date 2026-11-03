/* keyboard_entry_scene_4: 3 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a1ed0 @ 0x022a1ed0, 0x1e bytes, Thumb
 * func_ov126_022a1e8c @ 0x022a1e8c, 0x44 bytes, Thumb
 * func_ov126_022a1d90 @ 0x022a1d90, 0xfc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022a1ed0 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
};

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

extern void func_ov126_022a14d0(void *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern unsigned int func_0206fca4(void);
extern void *func_020ee45c(void *a);
extern int func_ov090_0229936c(void *x);
extern void func_ov090_022990d0(void *x);
extern void func_ov092_0229929c(void *x);
extern void func_ov126_022a149c(void *a);
extern int func_ov126_0229f7c8(UnkStruct_022a1d90 *self, int arg);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov124_0229eeb8(void *p, int a, u32 b);
extern int func_ov002_02207f60(UnkStruct_022a1d90 *self);
extern void func_ov002_0220ad18(void *p, int v);
extern void func_ov095_0229b1c8(void *p, int a, u32 b, int c);
extern void func_ov095_0229ae84(void *p, int a, u32 b);
extern void func_02088df8(int a1, void *a2, u32 a3, u32 a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12);
extern int func_ov095_0229af58(void *p, int a, int b, int c);
extern u8 data_ov126_022a20b0;

int func_ov126_022a1ed0(struct UnkStruct_022a1ed0 *self)
{
    func_ov126_022a14d0(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov126_022a1e8c(void *a)
{
    unsigned int res = func_0206fca4();
    if (res >= 24 && res <= 27) {
        void *x = func_020ee45c(a);
        if (func_ov090_0229936c(x) == 6) {
            func_ov090_022990d0(x);
        }
    } else {
        func_ov092_0229929c(func_020ee45c(a));
    }
    func_ov126_022a149c(a);
    return 1;
}

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
