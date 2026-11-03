/* map_menu_scene_2: 13 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229c404 @ 0x0229c404, 0x34 bytes, Thumb
 * func_ov118_0229c3d8 @ 0x0229c3d8, 0x2c bytes, Thumb
 * func_ov118_0229c3ac @ 0x0229c3ac, 0x2c bytes, Thumb
 * func_ov118_0229c378 @ 0x0229c378, 0x34 bytes, Thumb
 * func_ov118_0229c35c @ 0x0229c35c, 0x1c bytes, Thumb
 * func_ov118_0229c2a0 @ 0x0229c2a0, 0xbc bytes, Thumb
 * func_ov118_0229c240 @ 0x0229c240, 0x60 bytes, Thumb
 * func_ov118_0229c1ec @ 0x0229c1ec, 0x54 bytes, Thumb
 * func_ov118_0229c18c @ 0x0229c18c, 0x60 bytes, Thumb
 * func_ov118_0229c098 @ 0x0229c098, 0xf4 bytes, Thumb
 * func_ov118_0229c078 @ 0x0229c078, 0x1e bytes, Thumb
 * func_ov118_0229c070 @ 0x0229c070, 0x8 bytes, Thumb
 * func_ov118_0229bfa4 @ 0x0229bfa4, 0xcc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229c2a0 {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
    unsigned short unk_98;
} UnkStruct_0229c2a0;

typedef struct {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned short unk_98;
} UnkStruct_0229c1ec;

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

typedef struct {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0xa3 - 0x9a];
    u8 unk_A3;
    u8 pad_A4[0xb4 - 0xa4];
    u8 unk_B4[1];
    u8 pad_B5[0xd8 - 0xb5];
    u8 unk_D8[1];
    u8 pad_D9[0x724 - 0xd9];
    u8 unk_724[1];
    u8 pad_725[0xf24 - 0x725];
    u8 unk_F24[1];
} UnkStruct_0229bfa4;

extern void func_ov118_0229bf3c(void);
extern void func_ov118_0229be8c(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229be6c(void);
extern void func_ov118_0229be54(void);
extern void func_ov118_0229be04(void *);
extern void func_ov118_0229b454(void *arg);
extern void func_ov118_0229b778(void *arg);
extern void func_ov118_0229bda4(void);
extern void *func_020641c8(void *obj);
extern void func_02064210(const void *str, void *obj);
extern void *func_020b496c(int value, void *obj);
extern int func_ov118_0229b630(void *self);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern int func_0207094c(int a, int b);
extern void func_02070a04(int a, int b, int c);
extern void *func_020641b0(void *obj);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov118_0229a450(void *self, int n);
extern const char data_021dc7aa[];
extern int func_ov002_02207f48(void *p, int v);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern int func_0206fe60(void);
extern void func_ov118_0229b8b0(void *p);
extern void func_ov118_0229b868(void *p);
extern int func_ov002_02207f60(void *p);
extern void func_ov118_0229a92c(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(void *p, int v);
extern void func_020027f0(int v);
extern void func_ov118_0229a440(void *p, int v);
extern void func_ov118_0229afd4(UnkStruct_0229c098 *self, int a);
extern void func_ov118_0229b564(UnkStruct_0229c098 *self);
extern Vec3 *func_02095794(int a);
extern int func_020b5e10(void);
extern Vec3 *func_020b64ec(void *p);
extern void *func_0208e95c(void *p, int a);
extern int func_020ee45c(UnkStruct_0229c098 *self);
extern int func_ov090_02298f74(void *);
extern u8 data_020e54a8;
extern char data_021f69b8[];
extern void func_ov118_0229b664(void *arg0);
extern void func_020b9ccc(void *);
extern int func_ov118_0229add4(void *self);
extern void func_ov118_0229ad24(void *self);
extern void func_ov118_0229aad8(void *self);
extern void func_0200284c(int a, int b, int c);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);

void func_ov118_0229c3d8(int arg);
void func_ov118_0229c3ac(void *arg);
void func_ov118_0229c378(void *r0);
void func_ov118_0229c35c(void *arg);

void func_ov118_0229c404(void *param)
{
    func_ov118_0229bf3c();
    func_ov118_0229be8c(param);
    func_ov002_02208090(param, 1);
    if (func_ov118_0229a460(param, 0x2000) == 0) {
        func_ov118_0229c3d8((int) param);
    }
}

void func_ov118_0229c3d8(int arg)
{
    func_ov118_0229be6c();
    func_ov002_02208090((void *) arg, 2);
    if (func_ov118_0229a460((void *) arg, 0x2000) == 0) {
        func_ov118_0229c3ac((void *) arg);
    }
}

void func_ov118_0229c3ac(void *arg)
{
    func_ov118_0229be54();
    func_ov002_02208090(arg, 3);
    if (func_ov118_0229a460(arg, 0x2000) == 0) {
        func_ov118_0229c378(arg);
    }
}

void func_ov118_0229c378(void *r0)
{
    func_ov118_0229be04(r0);
    func_ov002_02208090(r0, 4);
    if (func_ov118_0229a460(r0, 0x2000) == 0) {
        func_ov118_0229c35c(r0);
        func_ov118_0229a440(r0, 0x2000);
    }
}

void func_ov118_0229c35c(void *arg)
{
    func_ov118_0229b454(arg);
    func_ov118_0229b778(arg);
    func_ov002_02208090(arg, 5);
}

void func_ov118_0229c2a0(UnkStruct_0229c2a0 *self)
{
    char obj[0x20];
    int r;

    func_ov118_0229bda4();
    func_020641c8(obj);
    func_02064210(data_021dc7aa, obj);
    func_020b496c(0, obj);
    r = func_ov118_0229b630(self);
    func_02070adc(r, 8, 0x1ab, 0x12, 0xf, 0, 0);
    func_0207094c(r, 0xa9);
    func_02070a04(r, 1, 0);
    func_020641b0(obj);
    func_ov002_02207f20(self, 0xa, 3, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80(self, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    func_ov118_0229a450(self, 4);
    self->unk_94 = (unsigned int) func_ov002_02207f60(self);
    func_ov002_02208090(self, 6);
}

void func_ov118_0229c240(char *p)
{
    unsigned short v;

    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        if (func_0206fe60()) {
            func_ov118_0229b8b0(p);
        } else {
            func_ov118_0229b868(p);
        }
    }
    func_ov002_02207e80(p, 4, 0, 0);
    v = *(unsigned short *) (p + 0x98);
    func_ov002_02207e80(p, 6, 0, 0x50 - v);
    *(int *) (p + 0x94) = func_ov002_02207f60(p);
}

void func_ov118_0229c1ec(UnkStruct_0229c1ec *self)
{
    func_ov118_0229a92c(self);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    func_ov002_02208090(self, 8);
    self->unk_94 = func_ov002_02207f60(self);
}

void func_ov118_0229c18c(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov118_0229a440(p, 4);
        func_ov002_022080a0(p, 5);
    } else {
        unsigned short v;
        func_ov002_02207e80(p, 4, 0, 0);
        v = *(unsigned short *) (p + 0x98);
        func_ov002_02207e80(p, 6, 0, 0x50 - v);
        *(int *) (p + 0x94) = func_ov002_02207f60(p);
    }
}

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
        func_ov118_0229a450((void *) self, 0x2000);
    }
}

void func_ov118_0229c078(void *param)
{
    void *p;
    func_ov118_0229b664((void *) param);
    p = (char *) param + 0xb4;
    func_020b9ccc(p);
    p = (char *) param + 0xd8;
    func_020b9ccc(p);
}

void func_ov118_0229c070(void *arg0)
{
    func_ov118_0229b664((void *) arg0);
}

void func_ov118_0229bfa4(UnkStruct_0229bfa4 *self)
{
    if (func_ov118_0229add4(self)) {
        func_ov118_0229ad24(self);
        func_0200284c(6, 0, self->unk_98 - 0x50);
        if (self->unk_A3 != (self->unk_98 >> 4)) {
            func_ov118_0229a450(self, 0x80);
        }
    }

    func_ov118_0229aad8(self);

    if (func_ov118_0229a460(self, 0x80) != 0) {
        func_ov118_0229b778(self);
        func_ov118_0229a440(self, 0x80);
    }

    if (func_ov118_0229a460(self, 0x20) != 0) {
        if (func_020b9bbc(&self->unk_D8, &self->unk_724, 4, 0x800, 0) != 0) {
            func_ov118_0229a440(self, 0x20);
        }
    }

    if (func_ov118_0229a460(self, 2) != 0) {
        if (func_020b9bbc(&self->unk_B4, &self->unk_F24, 6, 0x800, 0) != 0) {
            func_ov118_0229a440(self, 2);
        }
    }
}
