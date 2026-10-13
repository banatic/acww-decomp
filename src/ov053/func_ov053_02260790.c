/* func_ov053_02260790 @ 0x02260790, 0x104 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260790 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xba - 0xb8];
    u8 unk_BA;
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
} UnkStruct_02260790;

extern int func_020984e8(void);
extern int func_020160b4(UnkStruct_02260790 *self);
extern int func_020ab504(int a);
extern void func_0208b520(void);
extern int func_0201b43c(int a, int b);
extern void func_0201b420(int a, int b);
extern int func_0208602c(void);
extern void func_020860f0(int a, int b);
extern int func_02099824(int t);
extern int func_020997f8(int t);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov053_02261980;
extern u8 data_ov053_022617c4[];
extern u8 data_ov053_022617c0[];

void func_ov053_02260790(UnkStruct_02260790 *self)
{
    u8 arg;
    int t;
    int a;
    int k;
    int code;

    t = func_020984e8();
    a = func_020ab504(func_020160b4(self));
    k = data_ov053_02261980;
    code = 0xff;
    switch (self->unk_1E) {
        case 1:
        case 2:
        case 4:
            if (a == 0) {
                func_0208b520();
                code = 8;
            }
            break;
        case 8:
            if (a == 0) {
                if (func_0201b43c(self->unk_B4, 0xbb8) != 0) {
                    func_0201b420(self->unk_B4, 0xbb8);
                    code = 0x3c;
                    func_020860f0(func_0208602c(), 7);
                    self->unk_BA = 0;
                    self->unk_BB = 0;
                    self->unk_BC = (u8) func_02099824(t);
                    self->unk_BD = (u8) func_020997f8(t);
                } else {
                    code = 0x3f;
                }
            }
            break;
        case 9:
        case 10:
            if (a != 4) {
                self->unk_BB = data_ov053_022617c4[a];
                code = 0xc;
            }
            break;
        case 11:
        case 0x38:
            if (a != 4) {
                self->unk_BB = data_ov053_022617c0[a];
                code = 0xc;
            }
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, k);
    }
}
