/* func_ov122_022a05d0 @ 0x022a05d0, 0x118 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb6];
    volatile u8 unk_B6;
    char pad_B7[0x4058 - 0xb7];
    char unk_4058;
    char pad_4059[0x4698 - 0x4059];
    char unk_4698;
} UnkStruct_022a05d0;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} Glob;

extern int func_ov002_02208014(void);
extern void func_ov122_022a0000(UnkStruct_022a05d0 *self);
extern int func_ov002_02208008(UnkStruct_022a05d0 *self);
extern void func_ov122_0229f348(UnkStruct_022a05d0 *self, int a);
extern void func_ov002_0220a1dc(void *p);
extern int func_ov002_022088ac(int pad);
extern int func_ov002_0220889c(int pad);
extern int func_ov002_0220a768(void *p, int a);
extern int func_ov002_0220a72c(void *p, int a);
extern void func_ov122_0229f21c(UnkStruct_022a05d0 *self, int a, int b);
extern void func_ov122_0229f2d0(UnkStruct_022a05d0 *self);

extern Glob data_021fbe40;
extern u8 data_ov122_022a2580[];

void func_ov122_022a05d0(UnkStruct_022a05d0 *self)
{
    int pad;
    u8 old;
    u8 nw;
    u16 t;

    if (func_ov002_02208014() != 0) {
        func_ov122_022a0000(self);
        return;
    }
    pad = func_ov002_02208008(self);
    t = data_021fbe40.unk_02;
    if ((t & 1) != 0) {
        switch (self->unk_B6) {
            case 0:
                func_ov122_0229f348(self, 3);
                break;
            case 1:
                func_ov122_0229f348(self, 4);
                break;
        }
        func_ov002_0220a1dc(&self->unk_4058);
        return;
    }
    old = self->unk_B6;
    if (func_ov002_022088ac(pad) != 0) {
        if (self->unk_B6 != 0) {
            self->unk_B6 = self->unk_B6 - 1;
        }
    } else if (func_ov002_0220889c(pad) != 0) {
        if (self->unk_B6 < 1) {
            self->unk_B6 = self->unk_B6 + 1;
        }
    }
    nw = self->unk_B6;
    if (old != nw) {
        int a = func_ov002_0220a768(&self->unk_4698, data_ov122_022a2580[nw]);
        int b = func_ov002_0220a72c(&self->unk_4698, data_ov122_022a2580[nw]);
        func_ov122_0229f21c(self, a, b);
    } else {
        t = data_021fbe40.unk_02;
        if ((t & 8) != 0) {
            func_ov122_0229f2d0(self);
            func_ov122_0229f348(self, 3);
        } else if ((t & 2) != 0) {
            func_ov122_0229f2d0(self);
            func_ov122_0229f348(self, 4);
        }
    }
}
