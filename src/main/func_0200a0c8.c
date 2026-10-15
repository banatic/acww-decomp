/* func_0200a0c8 @ 0x0200a0c8, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern void *data_020d730c;
extern s16 FX_SinCosTable_[];

extern int func_02073908(void *a, int b);
extern int func_02057c44(int *pos);
extern int func_02057c68(void *self);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int dx, int dz);
extern int func_020e8b4c(int a, int b);
extern int func_0200e9a8(void *self, s16 *ang, int *tx, int *tz, s16 *out_ang);
extern void func_0201107c(void *self, void *ptr);
extern int func_020113e0(s16 *ang, s16 val);
extern void func_020110a0(void *self, s16 *ang);
extern int FX_MulFunc(int a, s16 b);

typedef struct UnkStruct_0200a0c8 {
    u8 pad_00[0x5c];
    int x;
    int y;
    int z;
    u8 pad_68[0x8e - 0x68];
    s16 ang;
    u8 pad_90[0x7d4 - 0x90];
    int p7;
    u8 pad_7D8[0x800 - 0x7d8];
    int unk_800;
} UnkStruct_0200a0c8;

typedef struct Frame {
    s16 ang[4];
    int res;
    int pos[3];
    int target_pos[3];
    int dx;
    int pad_28;
    int dz;
} Frame;

void func_0200a0c8(UnkStruct_0200a0c8 *self)
{
    int *p7;
    Frame data;
    int *p;
    int angle;
    int res;

    p7 = &self->p7;
    p = (int *) ((char *) self + 0x5c);
    data.pos[0] = p[0];
    data.pos[1] = p[1];
    data.pos[2] = p[2];
    data.ang[2] = *(s16 *) ((char *) self + 0x8e);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        if (func_02057c44(data.target_pos) == 0) {
            return;
        }
        data.dx = data.target_pos[0] - self->x;
        data.dz = data.target_pos[2] - self->z;
        if (func_02057c68(self) != 0) {
            *p7 = 0;
        } else {
            *p7 = func_020113b0(*p7, 0x333);
        }
        data.ang[1] = (s16) func_020e8ed8(data.dx, data.dz);
    } else {
        if (func_0200e9a8(self, data.ang, &data.target_pos[0], &data.target_pos[2], &data.ang[1]) == 0) {
            func_0201107c(self, &data_020d730c);
            return;
        }
        if (data.target_pos[0] != self->x || data.target_pos[2] != self->z) {
            data.dx = data.target_pos[0] - self->x;
            data.dz = data.target_pos[2] - self->z;
            *p7 = func_020113b0(*p7, 0x333);
            angle = func_020e8ed8(data.dx, data.dz);
            if (func_020e8b4c(angle, data.ang[2]) >= 0x4000) {
                *p7 = 0;
            } else {
                data.ang[1] = (s16) angle;
            }
        } else {
            *p7 = 0;
        }
    }

    if (*p7 != 0) {
        func_020113e0(&data.ang[2], data.ang[1]);
        func_020110a0(self, &data.ang[2]);
    }

    res = FX_MulFunc(*p7, FX_SinCosTable_[((u16) (s16) (data.ang[2] - data.ang[1]) >> 4) * 2 + 1]);
    if (res < 0) {
        res = -res;
    }
    data.res = res;
    func_0201107c(self, &data.res);
}
