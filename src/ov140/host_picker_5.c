/* host_picker_5: 11 functions, module ov140
 * mwccarm 1.2/base -O4,s
 * func_ov140_0229aebc @ 0x0229aebc, 0x4 bytes, Thumb
 * func_ov140_0229aeb8 @ 0x0229aeb8, 0x4 bytes, Thumb
 * func_ov140_0229ae74 @ 0x0229ae74, 0x44 bytes, Thumb
 * func_ov140_0229ae44 @ 0x0229ae44, 0x30 bytes, Thumb
 * func_ov140_0229adf8 @ 0x0229adf8, 0x4c bytes, Thumb
 * func_ov140_0229add0 @ 0x0229add0, 0x28 bytes, Thumb
 * func_ov140_0229ad98 @ 0x0229ad98, 0x38 bytes, Thumb
 * func_ov140_0229ad6c @ 0x0229ad6c, 0x2a bytes, Thumb
 * func_ov140_0229ad4c @ 0x0229ad4c, 0x1e bytes, Thumb
 * func_ov140_0229acc0 @ 0x0229acc0, 0x8c bytes, Thumb
 * func_ov140_0229ac8c @ 0x0229ac8c, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
} UnkStruct_0229ae74;

extern int func_ov140_02299fb0(UnkStruct_0229ae74 *p, int a);
extern void func_0206fc4c(int arg);
extern void func_0206fc80(int arg);
extern void func_0206f7c8(void);
extern void func_020ee470(UnkStruct_0229ae74 *p);
extern void func_ov140_0229abcc(void);
extern void func_ov140_0229ab94(void *);
extern void func_ov140_0229ab70(void *);
extern void func_ov139_022997f0(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov140_0229a1c4(void *);
extern void func_ov140_0229a280(void *);
extern void func_ov140_0229a164(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov140_02299fa0(void *, int);
extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov140_0229a7ac(int a);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int x);
extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);
extern void func_ov139_02299af8(u8 *p, int a, int b);
extern void func_ov140_0229a3fc(u8 *self, int a);
extern void func_020b9ccc(void *);
extern void func_ov140_0229a100(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov139_02299adc(void *);

int func_ov140_0229ad4c(int param);

int func_ov140_0229aebc(void)
{
    return 1;
}

int func_ov140_0229aeb8(void)
{
    return 1;
}

int func_ov140_0229ae74(UnkStruct_0229ae74 *p)
{
    if (func_ov140_02299fb0(p, 2) != 0) {
        func_0206fc4c(0);
    } else {
        func_0206fc4c(1);
        func_0206fc80(*(unsigned char *) ((char *) p + p->unk_9C + 0x8d5));
    }
    func_0206f7c8();
    func_020ee470(p);
    return 1;
}

void func_ov140_0229ae44(void *self)
{
    func_ov140_0229abcc();
    func_ov140_0229ab94(self);
    func_ov140_0229ab70(self);
    func_ov139_022997f0((char *) self + 0x8e8);
    func_ov002_02208090(self, 1);
}

void func_ov140_0229adf8(void *r0)
{
    void *r4 = r0;
    func_ov140_0229a1c4(r4);
    func_ov140_0229a280(r4);
    func_ov140_0229a164(r4, 5);
    func_ov002_02207f20(r4, 8, 4, 0, 0x30);
    func_02002708(6);
    func_ov140_0229ad4c((int) r4);
    func_ov140_02299fa0(r4, 1);
    func_ov002_02208090(r4, 2);
}

void func_ov140_0229add0(int param)
{
    if (func_ov002_02207f48(param, 0) != 0) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov140_0229a7ac(param);
    }
    func_ov140_0229ad4c(param);
}

void func_ov140_0229ad98(void *arg)
{
    int v = func_020ee45c(arg);
    func_ov092_02299324(v, 0x44, 1);
    func_ov002_02207f04(arg, 8, 0, 0, 0x30);
    func_ov140_0229ad4c((int) arg);
    func_ov002_02208090(arg, 4);
}

int func_ov140_0229ad6c(int arg)
{
    if (func_ov002_02207f3c(arg, 0) != 0) {
        func_020027f0(6);
        return (int) func_ov002_022080a0((void *) (arg), 5);
    } else {
        return func_ov140_0229ad4c(arg);
    }
}

int func_ov140_0229ad4c(int param)
{
    int *ptr;
    int result;

    func_ov002_02207e80(param, 6, 0, 0);
    result = func_ov002_02207f60(param);
    ptr = (int *) (param + 0x94);
    *ptr = result;
    return result;
}

void func_ov140_0229acc0(u8 *self)
{
    int i;
    int j;

    *(u16 *) (self + 0x8ac) = 0;
    func_ov139_02299af8(self + 0x8e8, 6, 0x7f);
    for (i = 0; i < 6; i++) {
        (self + i)[0x8af] = 0;
        (self + i)[0x8e0] = 0;
    }
    for (j = 0; j < 0x20; j++) {
        (self + j)[0x8b5] = 0xff;
    }
    func_ov140_0229a3fc(self, -1);
    *(int *) (self + 0xa4) = 8;
    *(int *) (self + 0xa8) = 9;
    self[0x8dc] = 0;
    self[0x8dd] = 0;
    self[0x8de] = 0;
}

void func_ov140_0229ac8c(void *self)
{
    func_ov002_0220af74((char *) self + 0x12f0);
    func_ov139_02299adc((char *) self + 0x8e8);
    func_020b9ccc((char *) self + 0x14bc);
    func_ov140_0229a100(self);
}
