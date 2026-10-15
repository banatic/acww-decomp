/* func_ov004_0223f218 @ 0x0223f218, 0x180 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int storage[39];
} Collider;
extern u8 data_ov004_02259a24, data_ov004_02259a34[];
extern void *func_020324fc(Collider *);
extern void *func_020324c4(Collider *);
extern int func_02032180(Collider *);
extern void func_ov004_0223f110(void *);
extern void func_ov004_0223f6dc(void *, void *);
extern void func_ov004_0223f41c(void *, void *);
extern int func_020321bc(Collider *, int, int, int, Vec *, short, Vec *);
int func_ov004_0223f218(u8 *self)
{
    u8 hit[3], type[3];
    Vec centers[3];
    Collider collision[3];
    u8 count, i;
    u8 *record;
    func_020324fc(&collision[0]);
    func_020324fc(&collision[1]);
    func_020324fc(&collision[2]);
    if (*(int *) (self + 8) == 0) {
        centers[0].x = 0x3800;
        centers[0].z = 0x8000;
        type[0] = 0;
        centers[1].x = 0x3800;
        centers[1].z = 0x1a000;
        type[1] = 0;
        centers[2].x = 0x16000;
        centers[2].z = 0x1c800;
        type[2] = 1;
        count = 3;
    } else {
        centers[0].x = 0x1c800;
        centers[0].z = 0x8000;
        type[0] = 0;
        centers[1].x = 0x1c800;
        centers[1].z = 0x1a000;
        type[1] = 0;
        count = 2;
    }
    for (i = 0; i < count; ++i) {
        if (type[i]) {
            hit[i] = func_020321bc(&collision[i], 0x4000, 0x1000, 0x6000, &centers[i], 0, 0);
        } else {
            hit[i] = func_020321bc(&collision[i], 0x1000, 0x4000, 0x6000, &centers[i], 0, 0);
        }
    }
    record = data_ov004_02259a34;
    data_ov004_02259a24++;
    func_ov004_0223f110(self);
    for (i = 0; i < 32; record += 0x2d8, ++i) {
        switch (*(int *) (record + 0x198)) {
            case 1:
                func_ov004_0223f6dc(self, record);
                break;
            case 2:
                func_ov004_0223f41c(self, record);
                break;
        }
    }
    for (i = 0; i < count; ++i) {
        if (hit[i]) {
            func_02032180(&collision[i]);
        }
    }
    func_020324c4(&collision[2]);
    func_020324c4(&collision[1]);
    func_020324c4(&collision[0]);
    return 1;
}
