/* func_020f6ba0 @ 0x020f6ba0, 0x1d8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

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

extern struct Glb data_021fd1bc;
extern const u8 data_02138fd4[];

extern int func_020f6d78(void *obj, u8 byte);
extern int func_020f1d3c(void *ptr, int arg);
extern void func_020eedb8(u16 arg1, u16 arg2, void *obj);
extern void func_0210b604(void *obj, int val);
extern void NNS_SndPlayerSetVolume(void *obj, int vol);
extern void NNS_SndPlayerSetTrackVolume(void *obj, int track, int vol);
extern void func_0210b634(void *obj, int track, int vol);
extern int _s32_div_f(int dividend, int divisor);

void func_020f6ba0(struct Param *param)
{
    int r6;
    int r5;
    int vol;
    struct UnkStruct_020f6ba0 *inner;

    r6 = func_020f6d78(param, param->unk_0B);
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
    if (param->unk_0B == data_02138fd4[0]) {
        vol = 0x40;
    } else if (param->unk_0B == data_02138fd4[1]) {
        vol = 0x50;
    } else if (param->unk_0B == data_02138fd4[2]) {
        vol = 0x60;
    } else if (param->unk_0B == data_02138fd4[3]) {
        vol = 0x70;
    } else if (param->unk_0B == data_02138fd4[4]) {
        vol = 0x7f;
    } else if (param->unk_0B == data_02138fd4[5]) {
        vol = 0x7f;
    } else if (param->unk_0B == data_02138fd4[6]) {
        vol = 0x70;
    } else if (param->unk_0B == data_02138fd4[7]) {
        vol = 0x60;
    } else if (param->unk_0B == data_02138fd4[8]) {
        vol = 0x50;
    } else if (param->unk_0B == data_02138fd4[9]) {
        vol = 0x40;
    } else if (param->unk_0B == data_02138fd4[10]) {
        vol = 0x30;
    } else if (param->unk_0B == data_02138fd4[11]) {
        vol = 0x20;
    } else if (param->unk_0B == data_02138fd4[12]) {
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