/* func_ov004_0223df88 @ 0x0223df88, 0x268 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};
struct Collider;
extern "C" {
void func_020324fc(Collider *);
void func_020324c4(Collider *);
int FX_Div(int, int);
int FX_MulFunc(int, int);
int func_020b6804(void);
int func_020321bc(Collider *, int, int, int, Vec *, short, Vec *);
void func_ov004_0223d63c(char *);
void func_02003244(void *, void *);
void func_02031288(void *, Vec *, Vec *, int, int, void *, int);
void func_02032180(Collider *);
}
struct Collider {
    int storage[39];
};
extern "C" void func_ov004_0223df88(char *self)
{
    int angle;
    Vec *position;
    int first, second;
    u8 hit[4], type[4];
    Vec centers[4];
    Collider collision[4];
    u8 count, i;
    int scale;
    func_020324fc(&collision[0]);
    func_020324fc(&collision[1]);
    func_020324fc(&collision[2]);
    func_020324fc(&collision[3]);
    position = (Vec *) (self + 0x5c);
    count = 1;
    angle = *(short *) (self + 0x8e);
    scale = FX_Div(0x1000, 0x2000);
    switch (func_020b6804()) {
        case 1:
        case 4:
            centers[0].x = FX_MulFunc(0x20000, scale);
            centers[0].z = FX_MulFunc(0x39000, scale);
            type[0] = 1;
            break;
        case 2:
            centers[0].x = FX_MulFunc(0x13000, scale);
            centers[0].z = FX_MulFunc(0x35000, scale);
            type[0] = 0;
            break;
        case 3:
            centers[0].x = FX_MulFunc(0x2c000, scale);
            centers[0].z = FX_MulFunc(0x37000, scale);
            type[0] = 0;
            break;
        case 0:
            count = 4;
            centers[0].x = FX_MulFunc(0xf000, scale);
            centers[0].z = FX_MulFunc(0x34000, scale);
            type[0] = 0;
            centers[1].x = FX_MulFunc(0x31000, scale);
            centers[1].z = FX_MulFunc(0x34000, scale);
            type[1] = 0;
            centers[2].x = FX_MulFunc(0x20000, scale);
            centers[2].z = FX_MulFunc(0x39000, scale);
            type[2] = 1;
            centers[3].x = FX_MulFunc(0x20000, scale);
            centers[3].z = FX_MulFunc(0x17000, scale);
            type[3] = 1;
            break;
    }
    for (i = 0; i < count; ++i) {
        if (type[i]) {
            first = FX_MulFunc(0x4000, 0x1000);
            hit[i] = func_020321bc(&collision[i], first, 0x1000, FX_MulFunc(0xa000, 0x1000), &centers[i], 0, 0);
        } else {
            second = FX_MulFunc(0x4000, 0x1000);
            hit[i] = func_020321bc(&collision[i], 0x1000, second, FX_MulFunc(0xa000, 0x1000), &centers[i], 0, 0);
        }
    }
    if (*(int *) (self + 0x10c)) {
        func_ov004_0223d63c(self);
    }
    func_02003244(self, self + 0x1d8);
    func_02031288(self + 0xdc, position, (Vec *) (self + 0x68), angle, 0x666, self, 15);
    for (i = 0; i < count; ++i) {
        if (hit[i]) {
            func_02032180(&collision[i]);
        }
    }
    func_020324c4(&collision[3]);
    func_020324c4(&collision[2]);
    func_020324c4(&collision[1]);
    func_020324c4(&collision[0]);
}
