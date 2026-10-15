/* func_ov120_0229bc74 @ 0x0229bc74, 0xd8 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x94];
    int unk_94;
    u16 unk_98;
    u16 unk_9A;
    u16 unk_9C;
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    char pad_A1[3];
    u8 unk_A4;
    char pad_A5[2];
    u8 unk_A7;
    char pad_A8[3];
    u8 unk_AB;
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
    char pad_AF[0x674 - 0xaf];
    char unk_674;
} UnkStruct_0229bc74;

extern void func_ov120_0229adc4(UnkStruct_0229bc74 *self, int a);
extern void func_ov120_0229b33c(UnkStruct_0229bc74 *self);
extern Vec3 *func_02095794(int a);
extern int func_020b5e10(void);
extern Vec3 *func_020b64ec(void *p);
extern void func_0208e95c(void *p, int a);
extern u8 data_020e54a8;
extern char data_021f69b8[];

void func_ov120_0229bc74(UnkStruct_0229bc74 *self)
{

    volatile Vec3 v;
    unsigned int ok;
    int a, b;
    Vec3 *p;

    self->unk_A0 = 0;
    self->unk_9C = 0;
    self->unk_98 = 0;
    self->unk_9A = 0;
    self->unk_A4 = 0;
    self->unk_94 = 0;
    self->unk_A7 = 0;
    self->unk_AB = 0;
    self->unk_AD = 0x58;
    self->unk_AE = 0x70;
    self->unk_AC = 0xe;
    func_ov120_0229adc4(self, 0);
    func_ov120_0229b33c(self);
    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok != 0) {
        p = func_02095794(4);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
    } else {
        func_020b5e10();
        p = func_020b64ec(data_021f69b8);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
    }
    a = (v.z + 0x800) >> 12;
    b = (v.x + 0x800) >> 12;
    self->unk_9E = (u8) (b - 8);
    self->unk_9F = (u8) (a + 0xd);
    func_0208e95c(&self->unk_674, 1);
}
