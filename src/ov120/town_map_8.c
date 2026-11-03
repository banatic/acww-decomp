/* town_map_8: 16 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229c028 @ 0x0229c028, 0x1c bytes, Thumb
 * func_ov120_0229c024 @ 0x0229c024, 0x4 bytes, Thumb
 * func_ov120_0229c020 @ 0x0229c020, 0x4 bytes, Thumb
 * func_ov120_0229c010 @ 0x0229c010, 0x10 bytes, Thumb
 * func_ov120_0229bfe8 @ 0x0229bfe8, 0x28 bytes, Thumb
 * func_ov120_0229bfcc @ 0x0229bfcc, 0x1c bytes, Thumb
 * func_ov120_0229bfb4 @ 0x0229bfb4, 0x16 bytes, Thumb
 * func_ov120_0229bf98 @ 0x0229bf98, 0x1c bytes, Thumb
 * func_ov120_0229bedc @ 0x0229bedc, 0xbc bytes, Thumb
 * func_ov120_0229be00 @ 0x0229be00, 0xdc bytes, Thumb
 * func_ov120_0229bdac @ 0x0229bdac, 0x54 bytes, Thumb
 * func_ov120_0229bd4c @ 0x0229bd4c, 0x60 bytes, Thumb
 * func_ov120_0229bc74 @ 0x0229bc74, 0xd8 bytes, Thumb
 * func_ov120_0229bc54 @ 0x0229bc54, 0x1e bytes, Thumb
 * func_ov120_0229bc4c @ 0x0229bc4c, 0x8 bytes, Thumb
 * func_ov120_0229bb80 @ 0x0229bb80, 0xcc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229bfe8 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
};

typedef struct GXDLInfo GXDLInfo;

typedef struct UnkStruct_0229bedc {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
    unsigned short unk_98;
} UnkStruct_0229bedc;

typedef struct {
    u8 pad_00[0x94];
    int unk_94;
    u16 unk_98;
    u8 pad_9A[0xAC - 0x9A];
    u8 unk_AC;
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_AF[0x2743 - 0xAF];
    u8 table[1024];
} UnkStruct_0229be00;

typedef struct {
    char pad_00[0x94];
    int unk_94;
    unsigned short unk_98;
} UnkStruct_0229bd4c;

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

extern void func_ov120_0229bb54(int arg);
extern void func_ov120_0229c044(int arg);
extern void func_ov120_0229bb4c(int arg);
extern void func_020ee470(void *parameter0);
extern int func_020ee45c(struct UnkStruct_0229bfe8 *obj);
extern void func_ov092_02299324(int a, int b, int c);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229bfe8 *obj, unsigned char value);
extern void func_ov120_0229bb18(void);
extern void func_ov120_0229ba68(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov120_0229b9dc(GXDLInfo *info);
extern void func_ov120_0229b22c(void *);
extern void func_ov120_0229b548(void *);
extern void func_ov120_0229b97c(void);
extern void *func_020641c8(void *p);
extern void func_02064210(unsigned char *s, void *p);
extern void *func_020b496c(int a, void *p);
extern void *func_ov120_0229b400(UnkStruct_0229bedc *self);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern int func_0207094c(void *p, int a);
extern void func_02070a04(void *p, int a, int b);
extern void *func_020641b0(void *p);
extern void func_ov002_02207f20(UnkStruct_0229bedc *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov120_0229a438(UnkStruct_0229bedc *self, int a);
extern unsigned int func_ov002_02207f60(UnkStruct_0229bedc *self);
extern unsigned char data_021dc7aa[];
extern int func_ov002_02207f48(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov120_0229b604(UnkStruct_0229be00 *);
extern void func_ov120_0229a7a8(void *self);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern int func_ov002_02207f3c(UnkStruct_0229bd4c *, int);
extern void func_020027f0(int);
extern void func_ov120_0229a428(UnkStruct_0229bd4c *, int);
extern void func_ov120_0229adc4(UnkStruct_0229bc74 *self, int a);
extern void func_ov120_0229b33c(UnkStruct_0229bc74 *self);
extern Vec3 *func_02095794(int a);
extern int func_020b5e10(void);
extern Vec3 *func_020b64ec(void *p);
extern void *func_0208e95c(void *p, int a);
extern u8 data_020e54a8;
extern char data_021f69b8[];
extern void func_ov120_0229b434(char *);
extern void func_020b9ccc(char *);
extern int func_ov120_0229abd0(unsigned char *self);
extern void func_ov120_0229ab20(unsigned char *self);
extern void func_0200284c(int a, int b, int c);
extern void func_ov120_0229a928(unsigned char *self);
extern int func_ov120_0229a448(unsigned char *self, int v);
extern int func_020b9bbc(unsigned char *a, unsigned char *b, int c, int d, int e);

int func_ov120_0229c028(int arg)
{
    func_ov120_0229bb54(arg);
    func_ov120_0229c044(arg);
    func_ov120_0229bb4c(arg);
    return 1;
}

int func_ov120_0229c024(void)
{
    return 1;
}

int func_ov120_0229c020(void)
{
    return 1;
}

int func_ov120_0229c010(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

int func_ov120_0229bfe8(struct UnkStruct_0229bfe8 *obj)
{
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    obj->unk_8C = 5;
    func_ov002_022080a0(obj, 1);
    return 1;
}

void func_ov120_0229bfcc(void *param)
{
    func_ov120_0229bb18();
    func_ov120_0229ba68(param);
    func_ov002_02208090(param, 1);
}

void func_ov120_0229bfb4(GXDLInfo *info, int op, u32 param0, u32 param1)
{
    func_ov120_0229b9dc(info);

    func_ov002_02208090((void *) info, 2);
}

void func_ov120_0229bf98(void *r0)
{
    void *r4 = r0;
    func_ov120_0229b22c(r4);
    func_ov120_0229b548(r4);
    func_ov002_02208090(r4, 3);
}

void func_ov120_0229bedc(UnkStruct_0229bedc *self)
{
    void *p;
    unsigned char local[0x20];

    func_ov120_0229b97c();
    func_020641c8(local);
    func_02064210(data_021dc7aa, local);
    func_020b496c(0, local);

    p = func_ov120_0229b400(self);
    func_02070adc(p, 8, 0x1ab, 0x12, 0xf, 0, 0);
    func_0207094c(p, 0xa9);
    func_02070a04(p, 1, 0);
    func_020641b0(local);

    func_ov002_02207f20(self, 0xa, 0, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80((void *) self, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80((void *) self, 6, 0, 0x50 - self->unk_98);
    func_ov120_0229a438(self, 4);

    self->unk_94 = func_ov002_02207f60(self);
    func_ov002_02208090((void *) self, 4);
}

void func_ov120_0229be00(UnkStruct_0229be00 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0((struct UnkStruct_0229bfe8 *) self, 2);
        self->unk_AC = 8;
        self->unk_AD = self->table[self->unk_AC * 3];
        self->unk_AE = *(self->table + (self->unk_AC * 3) + 1);
        if (self->unk_AE > 4) {
            self->unk_AE -= 4;
        } else {
            self->unk_AE = 0;
        }
        if (self->unk_AD < 0xFC) {
            self->unk_AD += 4;
        } else {
            self->unk_AD = 0xFF;
        }
        func_ov120_0229a438((UnkStruct_0229bedc *) self, 0x800);
        func_ov120_0229b604(self);
    }
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    self->unk_94 = (int) func_ov002_02207f60((UnkStruct_0229bedc *) self);
}

void func_ov120_0229bdac(void *self)
{
    func_ov120_0229a7a8(self);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - *(unsigned short *) ((char *) self + 0x98));
    func_ov002_02208090(self, 6);
    *(void **) ((char *) self + 0x94) = (void *) func_ov002_02207f60((UnkStruct_0229bedc *) self);
}

void func_ov120_0229bd4c(UnkStruct_0229bd4c *arg0)
{
    if (func_ov002_02207f3c(arg0, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov120_0229a428(arg0, 4);
        func_ov002_022080a0((struct UnkStruct_0229bfe8 *) arg0, 5);
    } else {
        func_ov002_02207e80((void *) arg0, 4, 0, 0);
        func_ov002_02207e80((void *) arg0, 6, 0, 0x50 - arg0->unk_98);
        arg0->unk_94 = (int) func_ov002_02207f60((UnkStruct_0229bedc *) arg0);
    }
}

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

void func_ov120_0229bc54(char *p)
{
    func_ov120_0229b434(p);
    func_020b9ccc(p + 0xb0);
    p += 0xd4;
    func_020b9ccc(p);
}

void func_ov120_0229bc4c(void *arg0)
{
    func_ov120_0229b434((char *) ((void *) arg0));
}

void func_ov120_0229bb80(unsigned char *self)
{
    if (func_ov120_0229abd0(self) != 0) {
        func_ov120_0229ab20(self);
        func_0200284c(6, 0, (int) (*(unsigned short *) (self + 0x98)) - 0x50);
        if (*(unsigned char *) (self + 0xa3) != (int) (*(unsigned short *) (self + 0x98)) >> 4) {
            func_ov120_0229a438((UnkStruct_0229bedc *) self, 0x80);
        }
    }
    func_ov120_0229a928(self);
    if (func_ov120_0229a448(self, 0x80) != 0) {
        func_ov120_0229b548((void *) self);
        func_ov120_0229a428((UnkStruct_0229bd4c *) self, 0x80);
    }
    if (func_ov120_0229a448(self, 0x20) != 0) {
        if (func_020b9bbc(self + 0xd4, self + 0x720, 4, 0x800, 0) != 0) {
            func_ov120_0229a428((UnkStruct_0229bd4c *) self, 0x20);
        }
    }
    if (func_ov120_0229a448(self, 2) != 0) {
        if (func_020b9bbc(self + 0xb0, self + 0xf20, 6, 0x800, 0) != 0) {
            func_ov120_0229a428((UnkStruct_0229bd4c *) self, 2);
        }
    }
}
