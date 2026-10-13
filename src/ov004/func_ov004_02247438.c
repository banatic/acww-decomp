/* func_ov004_02247438 @ 0x02247438, 0x1fc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define W(p, o) (*(int *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
extern int data_020ca158[][3];
extern Vec data_021fbee8;
extern short FX_SinCosTable_[];
extern Vec *func_02095794(int);
extern int func_0203b0b8(Vec *, Vec *, Vec *, int *);
extern int FX_Div(int, int), FX_MulFunc(int, int);
extern void func_0203c9b0(void *, int, int, int);
extern int func_0203c1e0(void *, Vec *);
extern short func_0200322c(Vec *, Vec *);
extern int func_020b65c4(void);
#define ABS16(x) ((x) < 0 ? (short) -(x) : (x))
void func_ov004_02247438(u8 *self, u8 *motion)
{
    int amplitude, boundary, lateral, complement, ratio, depth;
    Vec target;
    Vec *player;
    int distance, angle, side;
    if (!motion) {
        motion = self + 0xfc;
    }
    player = func_02095794(4);
    distance = func_0203b0b8(player, (Vec *) (self + 0x1cc), (Vec *) (self + 0x110), &depth);
    if (distance < 0x4800) {
        distance = 0x4800;
    } else if (distance > 0xb000) {
        distance = 0xb000;
    }
    ratio = FX_Div(distance - 0x4800, 0x6800);
    complement = 0x1000 - ratio;
    W(self, 0x1e4) = complement;
    func_0203c9b0(self, 0xb, data_020ca158[W(self, 0x1f0)][W(self, 0x1ec)], ratio);
    target.x = data_021fbee8.x;
    target.y = data_021fbee8.y;
    target.z = data_021fbee8.z;
    if (player->z > W(self, 0x1d4)) {
        target.x = player->x;
        target.y = player->y;
        target.z = player->z;
    } else {
        target.x = W(self, 0x1cc);
        target.y = W(self, 0x1d0);
        target.z = W(self, 0x1d4);
    }
    boundary = func_0203c1e0(self, (Vec *) (motion + 0x14));
    lateral = 0;
    angle = func_0200322c((Vec *) (motion + 0x14), &target);
    distance = 0x2000 - ABS16(angle);
    if (distance < 0) {
        distance = 0;
    }
    amplitude = (short) FX_MulFunc(FX_MulFunc(distance >> 1, 0x2000), 0xe02);
    if (amplitude > 0xe02) {
        amplitude = 0xe02;
    }
    if (amplitude > 0 && !self[0x1f5]) {
        if (self[0x1f6] == 3) {
            if (angle > 0) {
                side = 1;
            } else {
                side = 2;
            }
            if (boundary == 1 && side == 1) {
                if (ABS16(angle) > 0x701) {
                    side = 0;
                } else {
                    side = 2;
                }
            }
            if (boundary == 2 && side == 2) {
                if (ABS16(angle) > 0x701) {
                    side = 0;
                } else {
                    side = 1;
                }
            }
            if (func_020b65c4() == 0x10) {
                side = 1;
            }
            self[0x1f6] = side;
        }
        if (self[0x1f6] == 1) {
            amplitude = (short) -amplitude;
        }
        if (self[0x1f6] != 0) {
            H(motion, 0) = FX_MulFunc(amplitude, complement);
            lateral = FX_MulFunc(depth, FX_SinCosTable_[(H(motion, 0) >> 4) * 2]);
        }
    }
    W(motion, 0x1c) += depth;
    W(motion, 0x14) += lateral;
}
