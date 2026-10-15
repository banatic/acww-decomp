/* func_ov003_0222bb0c @ 0x0222bb0c, 0x234 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222bb0c {
    int x, y, z;
};

struct UnkStruct_0222bb0c_2;
typedef void (UnkStruct_0222bb0c_2::*PMF)(void);

struct UnkStruct_0222bb0c_2 {
    u8 pad_00[0x7e];
    signed char unk_7E;
    u8 pad_7F[0x120 - 0x7f];
    UnkStruct_0222bb0c unk_120;
    u8 pad_12C[0x138 - 0x12c];
    volatile short unk_138;
    u8 pad_13A[2];
    int unk_13C;
    u8 pad_140[0x1fe - 0x140];
    u8 unk_1FE;
    u8 pad_1FF;
    u8 unk_200;
    u8 unk_201;
    u8 pad_202[0x210 - 0x202];
    u8 unk_210;
    u8 pad_211[0x218 - 0x211];
    int unk_218;
    u8 pad_21C[0x224 - 0x21c];
    u8 unk_224;
    u8 pad_225[0x248 - 0x225];
    int unk_248;
};

extern PMF data_ov003_0225f160[];

extern "C" {
extern void func_ov003_02229f00(void *a, UnkStruct_0222bb0c_2 *self);
extern int func_ov003_0222a16c(UnkStruct_0222bb0c_2 *self);
extern int func_ov003_0222a634(UnkStruct_0222bb0c_2 *self);
extern int func_ov003_022282b8(UnkStruct_0222bb0c_2 *self, void *p);
extern void func_0204f818(int *x, int *z, UnkStruct_0222bb0c *p);
extern int func_02031b5c(int x, int z);

void func_ov003_0222bb0c(UnkStruct_0222bb0c_2 *self)
{
    int px, pz;
    int r;
    int h;

    if (self->unk_7E == 0xb) {
        func_ov003_02229f00(&self->unk_248, self);
    }
    (self->*data_ov003_0225f160[self->unk_200])();
    if (self->unk_200 == 5) {
        r = 0;
    } else {
        r = func_ov003_0222a16c(self);
    }
    switch (r) {
        case 0:
            self->unk_201 = 0;
            break;
        case 1:
        case 3:
            if (self->unk_210 != 0) {
                self->unk_138 = (short) (self->unk_138 + 0x222);
            } else {
                self->unk_138 = (short) (self->unk_138 - 0x222);
            }
            break;
        case 2:
        case 4:
            if (self->unk_200 == 1) {
                if (self->unk_210 != 0) {
                    self->unk_138 = (short) (self->unk_138 + 0x222);
                } else {
                    self->unk_138 = (short) (self->unk_138 - 0x222);
                }
            }
            break;
        case 6:
            if (self->unk_200 != 4) {
                h = self->unk_138;
                if (h < 0x3556 || h > 0x4aaa) {
                    self->unk_138 = (short) (self->unk_138 - 0x555);
                }
            }
            break;
        case 7:
            if (self->unk_200 != 4) {
                h = self->unk_138;
                if (h > -0x3556 || h < -0x4aaa) {
                    self->unk_138 = (short) (self->unk_138 + 0x555);
                }
            }
            break;
        case 5:
            if ((u8) (self->unk_200 + 0xff) <= 1) {
                h = self->unk_138;
                if (h < 0) {
                    h = -h;
                }
                if (h < 0x7556) {
                    if (self->unk_210 != 0) {
                        self->unk_138 = (short) (self->unk_138 + 0x555);
                    } else {
                        self->unk_138 = (short) (self->unk_138 - 0x555);
                    }
                }
            }
            break;
    }
    self->unk_13C = self->unk_13C + 1;
    if (self->unk_224 != 7 && self->unk_200 != 5) {
        if (func_ov003_0222a634(self) != 0) {
            self->unk_13C = 0;
            self->unk_224 = 0;
        }
    } else {
        self->unk_224 = 0;
        switch (self->unk_1FE) {
            case 0:
            case 1:
            case 2:
            case 3:
                func_0204f818(&px, &pz, &self->unk_120);
                if (func_02031b5c(px, pz) == 1) {
                    func_ov003_022282b8(self, &self->unk_218);
                }
                break;
            case 5:
            case 6:
                func_0204f818(&px, &pz, &self->unk_120);
                if (func_02031b5c(px, pz) == 2) {
                    func_ov003_022282b8(self, &self->unk_218);
                }
                break;
        }
    }
}
}
