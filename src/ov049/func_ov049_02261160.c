/* func_ov049_02261160 @ 0x02261160, 0x98 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261160 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
} UnkStruct_02261160;

extern int func_0206837c(int h);
extern int func_020ab504(int a);
extern u8 data_ov049_02262dc0[];
extern int data_ov049_02263298;
extern void func_0206844c(int h, u8 *p, int k);
extern int func_0202ea40(void *p, u8 *q, int a);
extern void func_0202ea28(void *p, u8 *q);
extern int data_020ccf94;
extern int func_02073d90(int g);
extern short *func_0209d358(int a, int b);
extern int func_02082644(int a);
extern void func_020160d8(UnkStruct_02261160 *self, int a);

void func_ov049_02261160(UnkStruct_02261160 *self)
{
    u8 m[2];
    int k;
    int v;
    int r;

    v = (int) self->unk_1E;
    if (v >= 0 && v <= 0x11) {
        k = func_020ab504(func_0206837c(self->unk_40));
        if (k != 2) {
            m[1] = data_ov049_02262dc0[k];
            func_0206844c(self->unk_40, &m[1], data_ov049_02263298);
        } else if (func_0202ea40(self->unk_B0, m, 2) != 0) {
            func_0202ea28(self->unk_B0, m);
        }
    }
    if (func_02073d90(data_020ccf94) == 0 && *func_0209d358(0, 0x4a) == 0 && (r = func_02082644(5)) != 0) {
        func_020160d8(self, r);
    }
}
