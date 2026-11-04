/* sound_melody_7: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f6d78 @ 0x020f6d78, 0x13c bytes, ARM
 * func_020f6ba0 @ 0x020f6ba0, 0x1d8 bytes, ARM
 * func_020f6a80 @ 0x020f6a80, 0x120 bytes, ARM
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u8 *table;
    u8 pad_08[8];
    s8 state;
} Self2;

struct UnkStruct_020f6ba0 {
    u8 pad_00[0x39];
    s8 unk_39;
    s8 unk_3A;
};

struct Glb {
    u8 pad_00[0x30];
    struct UnkStruct_020f6ba0 *inner;
};

struct Param {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A;
    s8 unk_0B;
    u8 pad_0C[2];
    s8 unk_0E;
    u8 pad_0F;
    s8 unk_10;
};

typedef struct {
    u8 pad_00[0x14];
    u8 unk_14[0x14];
    u8 unk_28[0x11];
    s8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
} UnkStruct_020f6a80;

typedef struct {
    u8 pad_00[8];
    u16 unk_08;
    u8 pad_0A;
    s8 unk_0B;
    u8 pad_0C[2];
    s8 unk_0E;
    u8 pad_0F;
    s8 unk_10;
    s8 unk_11;
} Param;

typedef struct {
    u8 pad_00[0x30];
    UnkStruct_020f6a80 *inner;
} Glb;

typedef struct {
    u8 pad_00[0xc];
    u8 unk_0C;
} Misc;

extern u8 data_02138fd4[13];
extern struct Glb data_021fd1bc;
extern int func_020f1d3c(void *ptr, int arg);
extern int func_020eedb8(u16 arg1, u16 arg2, void *obj);
extern void func_0210b604(void *obj, int val);
extern void NNS_SndPlayerSetVolume(void *obj, int vol);
extern void NNS_SndPlayerSetTrackVolume(void *obj, int track, int vol);
extern void func_0210b634(void *obj, int track, int vol);
extern int _s32_div_f(int dividend, int divisor);
extern int func_020eed18(int, int);

u8 func_020f6d78(Self2 *self, u8 idx)
{
    u8 result;
    s8 state = self->state;

    switch (state) {
        case 0:
            result = self->table[idx];
            goto end;
        case 1: {
            u8 rem = idx % 3;
            if (rem == 1) {
                result = 0xe;
            } else {
                u8 q = idx / 3;
                if (rem == 0) {
                    result = self->table[q * 2];
                } else {
                    result = self->table[q * 2 + 1];
                }
            }
            goto end;
        }
        case 2: {
            u8 rem = idx % 3;
            if (rem == 2) {
                result = 0xe;
            } else {
                u8 q = idx / 3;
                if (rem == 0) {
                    result = self->table[q * 2];
                } else {
                    result = self->table[q * 2 + 1];
                }
            }
            goto end;
        }
        case 3: {
            int found = 0;
            int i;
            u8 *p = data_02138fd4;
            for (i = 0; i < 13; i++) {
                if (idx == *p) {
                    result = self->table[i];
                    found = 1;
                }
                p++;
            }
            if (!found) {
                result = 0xe;
            }
            goto end;
        }
    }

end:
    return result;
}

void func_020f6ba0(struct Param *param)
{
    int r6;
    int r5;
    int vol;
    struct UnkStruct_020f6ba0 *inner;

    r6 = (int) func_020f6d78((Self2 *) param, param->unk_0B);
    r5 = _s32_div_f(0x25800, 0x78 * (int) param->unk_0E);

    switch (r6) {
        case 13: {
            u16 value;
            value = (u16) (func_020f1d3c(&data_021fd1bc, 6) + (r6 + 1));
            func_020eedb8(value, param->unk_08, param);
            func_0210b604(param, r5);
            break;
        }
        case 14:
        case 15:
            break;
        default:
            func_020eedb8((u16) (r6 + 1), param->unk_08, param);
            func_0210b604(param, r5);
            break;
    }

    if (param->unk_10 != 3) {
        return;
    }

    vol = -1;
    if (param->unk_0B == ((const u8 *) data_02138fd4)[0]) {
        vol = 0x40;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[1]) {
        vol = 0x50;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[2]) {
        vol = 0x60;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[3]) {
        vol = 0x70;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[4]) {
        vol = 0x7f;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[5]) {
        vol = 0x7f;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[6]) {
        vol = 0x70;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[7]) {
        vol = 0x60;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[8]) {
        vol = 0x50;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[9]) {
        vol = 0x40;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[10]) {
        vol = 0x30;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[11]) {
        vol = 0x20;
    } else if (param->unk_0B == ((const u8 *) data_02138fd4)[12]) {
        vol = 0x10;
    } else {
        vol = -1;
    }

    if (vol != -1) {
        NNS_SndPlayerSetVolume(param, vol);
    }

    inner = data_021fd1bc.inner;
    NNS_SndPlayerSetTrackVolume(param, 0xff, inner->unk_39);
    func_0210b634(param, 0xff, inner->unk_3A);
}

int func_020f6a80(Param *self)
{
    s8 state = self->unk_10;
    u8 nextb;
    int result;

    if (state == 0) {
        if (self->unk_0B == 0xf) {
            func_020eed18((int) self, 0);
            (*(Glb *) &data_021fd1bc).inner->unk_3C = 0;
            return 1;
        }
    } else {
        u8 v = (u8) (s8) (state - 1);
        if (v <= 1) {
            if (self->unk_0B == 0x17) {
                func_020eed18((int) self, 0);
                (*(Glb *) &data_021fd1bc).inner->unk_3C = 0;
                return 1;
            }
        } else if (state == 3) {
            if (self->unk_0B == (*(Misc *) data_02138fd4).unk_0C + 6) {
                func_020eed18((int) self, 0);
                (*(Glb *) &data_021fd1bc).inner->unk_3C = 0;
                return 1;
            }
        }
    }

    nextb = (u8) (self->unk_0B + 1);
    result = (int) func_020f6d78((Self2 *) self, nextb);
    if (result == 0xe) {
        goto ret0;
    }
    if (result == 0xf) {
        if (self->unk_11 == 1) {
            goto ret0;
        }
    }
    func_020eed18((int) self, 0);
ret0:
    return 0;
}
