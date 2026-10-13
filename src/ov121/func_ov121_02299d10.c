/* func_ov121_02299d10 @ 0x02299d10, 0x124 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb1];
    volatile u8 unk_B1;
} UnkStruct_02299d10;

extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088ac(void *p);
extern void func_ov121_02299e54(UnkStruct_02299d10 *self);
extern int func_ov121_0229a00c(UnkStruct_02299d10 *self, int a, int b, int c);
extern int func_ov121_02299fe0(UnkStruct_02299d10 *self, int a, int b, int c);
extern int func_ov121_02299fc8(UnkStruct_02299d10 *self);
extern void func_ov121_02299e34(UnkStruct_02299d10 *self, int a);

void func_ov121_02299d10(UnkStruct_02299d10 *self, void *pad, int flag)
{
    u8 s;
    int r;

    if (func_ov002_022088cc(pad) != 0) {
        s = self->unk_B1;
        if (s == 8) {
            self->unk_B1 = 0;
            return;
        }
        if (s <= 3) {
            if (flag != 0) {
                self->unk_B1 = self->unk_B1 + 0xc;
            } else {
                func_ov121_02299e54(self);
            }
            return;
        }
        if (func_ov121_0229a00c(self, 4, 7, 0) != 0) {
            return;
        }
        s = self->unk_B1;
        if (s >= 9 && s <= 0xb) {
            if (flag != 0) {
                return;
            }
            func_ov121_02299e54(self);
            return;
        }
        if (s < 0xc || s > 0xf) {
            return;
        }
        if (func_ov002_0220889c(pad) != 0) {
            self->unk_B1 = self->unk_B1 - 1;
        }
        self->unk_B1 = self->unk_B1 - 3;
        if (self->unk_B1 > 0xb) {
            self->unk_B1 = 0xb;
        }
        return;
    }
    if (func_ov002_022088bc(pad) == 0) {
        return;
    }
    if (func_ov121_02299fe0(self, 0, 3, 4) != 0) {
        return;
    }
    r = func_ov121_02299fc8(self);
    if (r != -1) {
        func_ov121_02299e34(self, r);
        return;
    }
    if (func_ov121_02299fe0(self, 0xc, 0xf, 0) != 0) {
        return;
    }
    s = self->unk_B1;
    if (s < 9 || s > 0xb) {
        return;
    }
    if (func_ov002_022088ac(pad) != 0) {
        self->unk_B1 = self->unk_B1 + 1;
    }
    self->unk_B1 = self->unk_B1 + 3;
}
