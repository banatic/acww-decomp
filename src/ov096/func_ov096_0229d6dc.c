/* func_ov096_0229d6dc @ 0x0229d6dc, 0xf4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xac];
    u16 unk_AC;
    char pad_AE[0xb4 - 0xae];
    u8 unk_B4;
    char pad_B5[0xbb - 0xb5];
    u8 unk_BB;
    char pad_BC[0xc0 - 0xbc];
    u8 unk_C0;
} UnkStruct_0229d6dc;

extern u16 func_ov096_0229e4a4(UnkStruct_0229d6dc *self, int a);
extern void func_ov096_0229fb9c(UnkStruct_0229d6dc *self);
extern int func_ov096_0229f55c(void *receiver);
extern void func_ov096_0229f874(UnkStruct_0229d6dc *self, int a, int b, int c);
extern void func_0200467c(int a);
extern void func_ov096_0229e6a0(UnkStruct_0229d6dc *self);
extern void func_ov096_0229e67c(UnkStruct_0229d6dc *self);
extern void func_ov096_0229c2ec(UnkStruct_0229d6dc *self, int a);

void func_ov096_0229d6dc(UnkStruct_0229d6dc *self)
{
    volatile u16 t;
    int flag = 1;
    int r;

    t = 0xfff1;
    switch (self->unk_BB) {
        case 0xf:
            self->unk_C0 = 3;
            break;
        case 0x10: {
            unsigned int ok;
            u16 lo, hi;
            self->unk_C0 = 4;
            t = func_ov096_0229e4a4(self, 4);
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1429 && lo <= 0x1430) {
                ok = 1;
            }
            if (ok != 0) {
                flag = 0;
            }
        } break;
        case 0x11: {
            unsigned int ok;
            u16 lo, hi;
            self->unk_C0 = 5;
            t = func_ov096_0229e4a4(self, 5);
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x13a0 && lo <= 0x13a7) {
                ok = 1;
            }
            if (ok != 0) {
                flag = 0;
            }
        } break;
        default:
            func_ov096_0229fb9c(self);
            return;
    }

    r = func_ov096_0229f55c(self);
    if (flag != 0 && r == 0x26) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0xa, 0xff, 0);
        func_0200467c(0x73);
    } else {
        self->unk_B4 = (u8) r;
        func_ov096_0229e6a0(self);
        self->unk_AC = 0xfff1;
        func_ov096_0229e67c(self);
        func_ov096_0229c2ec(self, 0x8000);
    }
}
