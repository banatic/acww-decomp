/* func_ov118_0229c098 @ 0x0229c098, 0xf4 bytes, Thumb, module ov118
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
    char pad_A5[3];
    u8 unk_A8;
    char pad_A9[3];
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
    u8 unk_AF;
    char pad_B0[0x678 - 0xb0];
    char unk_678;
} UnkStruct_0229c098;

extern void func_ov118_0229afd4(UnkStruct_0229c098 *self, int a);
extern void func_ov118_0229b564(UnkStruct_0229c098 *self);
extern Vec3 *func_02095794(int a);
extern int func_020b5e10(void);
extern Vec3 *func_020b64ec(void *p);
extern void func_0208e95c(void *p, int a);
extern int func_020ee45c(UnkStruct_0229c098 *self);
extern int func_ov090_02298f74(void *);
extern void func_ov118_0229a450(UnkStruct_0229c098 *self, int a);
extern u8 data_020e54a8;
extern char data_021f69b8[];

void func_ov118_0229c098(UnkStruct_0229c098 *self)
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
    self->unk_A8 = 0;
    self->unk_AC = 8;
    self->unk_AE = 0x58;
    self->unk_AF = 0x70;
    self->unk_AD = 0xe;
    func_ov118_0229afd4(self, 0);
    func_ov118_0229b564(self);
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
    func_0208e95c(&self->unk_678, 1);
    if (func_ov090_02298f74((void *) func_020ee45c(self)) != 0) {
        func_ov118_0229a450(self, 0x2000);
    }
}
