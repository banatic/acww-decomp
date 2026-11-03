/* scene_lights_2: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020655c4 @ 0x020655c4, 0x40 bytes, Thumb
 * func_020655b8 @ 0x020655b8, 0xa bytes, Thumb
 * func_02065564 @ 0x02065564, 0x54 bytes, Thumb
 * func_02065560 @ 0x02065560, 0x2 bytes, Thumb
 * func_02065558 @ 0x02065558, 0x6 bytes, Thumb
 * func_0206553c @ 0x0206553c, 0x1c bytes, Thumb
 * func_02065520 @ 0x02065520, 0x1c bytes, Thumb
 * func_02065504 @ 0x02065504, 0x1c bytes, Thumb
 * func_020654d8 @ 0x020654d8, 0x2a bytes, Thumb
 * func_020654c8 @ 0x020654c8, 0x10 bytes, Thumb
 * func_02065450 @ 0x02065450, 0x78 bytes, Thumb
 * func_020653fc @ 0x020653fc, 0x54 bytes, Thumb
 * func_020653f0 @ 0x020653f0, 0xc bytes, Thumb
 * func_020653d0 @ 0x020653d0, 0x20 bytes, Thumb
 * func_020653b0 @ 0x020653b0, 0x20 bytes, Thumb
 * func_02065354 @ 0x02065354, 0x5c bytes, Thumb
 * func_02065334 @ 0x02065334, 0x20 bytes, Thumb
 * func_0206531c @ 0x0206531c, 0x18 bytes, Thumb
 * func_02065284 @ 0x02065284, 0x98 bytes, Thumb
 * func_02065268 @ 0x02065268, 0x1c bytes, Thumb
 * func_0206521c @ 0x0206521c, 0x4c bytes, Thumb
 * func_02065218 @ 0x02065218, 0x2 bytes, Thumb
 * func_020651b0 @ 0x020651b0, 0x68 bytes, Thumb
 * func_0206515c @ 0x0206515c, 0x54 bytes, Thumb
 * func_02065110 @ 0x02065110, 0x4c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02065564 {
    int state;
    int count;
};

typedef struct {
    int type;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int pad_14;
    int pad_18;
    int pad_1C;
    int pad_20;
    int unk_24;
} UnkStruct_02065450;

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020653fc;

typedef struct {
    char pad_00[20];
    int unk_14;
} UnkStruct_020653d0;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[14];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_020653b0;

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02065354;

struct UnkStruct_0206531c {
    unsigned char pad_00[4];
    unsigned short unk_04;
    unsigned char pad_06[14];
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
};

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02065284;

typedef union {
    struct {
        u8 a;
        u8 b;
    } unk_00;
    u16 raw;
} Pair;

typedef struct {
    int type;
    char pad_04[0xC];
    short unk_10;
    short unk_12;
} UnkStruct_02065110;

extern unsigned char data_020e54a8;
extern unsigned int data_021cd864;
extern unsigned int func_020bbef4(int);
extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_0200467c(int);
extern unsigned short data_020ccb6c[];
extern unsigned short data_020ccb68[];
extern int data_021c67a4;
int func_0203c590(int arg);
void func_020ea78c(void *ptr, int val);
extern void G3_MultMtx33(int);
extern void NNS_G3dGlbLightVector(int, short, short, short);
extern void NNS_G3dGlbLightColor(int, unsigned short);
extern unsigned short data_020ccb98[];
extern struct Global {
    unsigned char a;
    unsigned char b;
    int x;
    int y;
    int z;
    int w;
} data_021cd87c;
extern void func_0209def4(u16 *);
extern void func_0209ddd4(Pair p1, Pair p2, Pair *out);
extern int func_020ea838(int *);
extern int VEC_Mag(int *);
extern int FX_MulFunc(int, int);
extern void func_020ea6e0(int, int);

void func_020653d0(UnkStruct_020653d0 *param);
void func_020653b0(UnkStruct_020653b0 *s);
void func_02065354(UnkStruct_02065354 *p);
void func_02065334(void *param);
void func_0206531c(struct UnkStruct_0206531c *p);
void func_02065284(UnkStruct_02065284 *obj);
void func_0206515c(int *arg1, int *arg2);

unsigned int func_020655c4(unsigned int param0)
{
    unsigned int result;
    unsigned int flag;

    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        if (param0 == 0) {
            result = *(unsigned char *) (*(unsigned int *) &data_021cd864 + 0x178);
        } else {
            result = func_020bbef4(param0);
        }
    } else {
        result = func_020bbef4(param0);
    }
    return result;
}

void func_020655b8(int *p)
{
    p[0] = 2;
    p[1] = 0;
}

void func_02065564(struct UnkStruct_02065564 *p)
{
    if (p->state == 0) {
        p->count--;
        if (p->count < 0) {
            int arg;
            if (func_020b6660() != 0 || func_020b6640() != 0) {
                arg = data_020ccb6c[p->state];
            } else {
                arg = data_020ccb68[p->state];
            }
            func_0200467c(arg);
            p->state = 2;
        }
    } else {
        p->state = 2;
    }
}

void func_02065560(void *receiver) {}

void func_02065558(int *p, int a, int b)
{
    p[0] = a;
    p[1] = b;
}

void func_0206553c(void *arg0)
{
    int i;
    void *ptr;

    ptr = arg0;
    for (i = 0; i < 4; i++) {
        func_020655b8((int *) ptr);
    }
}

void func_02065520(void *arg0)
{
    int i;
    void *ptr;

    ptr = arg0;
    for (i = 0; i < 4; i++) {
        func_02065564((struct UnkStruct_02065564 *) ptr);
    }
}

void func_02065504(void *arg)
{
    int i;
    void *ptr = arg;

    for (i = 0; i < 4; i++) {
        func_02065560(ptr);
    }
}

void func_020654d8(void *param1, void *param2, void *param3)
{
    int i;
    int *p;

    i = 0;
    do {
        p = (int *) param1;
        if (*p == 2) {
            func_02065558((int *) param1, (int) param2, (int) param3);
        }
        i++;
    } while (i < 4);
}

void func_020654c8(void *r0)
{
    *(int *) r0 = 9;
    func_0206553c((char *) r0 + 0x24);
}

void func_02065450(UnkStruct_02065450 *obj)
{
    int local[3];
    int r;

    switch (obj->type) {
        case 0:
            func_020653d0((UnkStruct_020653d0 *) obj);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            func_02065334((void *) obj);
            break;
    }

    if (data_021c67a4) {
        r = func_0203c590(data_021c67a4);
        func_020ea78c(&obj->unk_08, r);
    }

    local[0] = obj->unk_08;
    local[1] = obj->unk_0C;
    local[2] = obj->unk_10;
    func_0206515c(local, &obj->unk_08);
    func_02065520((void *) (&obj->unk_24));
}

void func_020653fc(UnkStruct_020653fc *p, int arg)
{
    if (p->unk_00 != 9) {
        *(volatile unsigned int *) 0x04000440 = 2;
        *(volatile unsigned int *) 0x04000454 = 0;
        G3_MultMtx33(arg);
        NNS_G3dGlbLightVector(2, p->unk_08, p->unk_0C, p->unk_10);
        NNS_G3dGlbLightColor(2, p->unk_04);
    } else {
        NNS_G3dGlbLightColor(2, 0);
    }
}

void func_020653f0(void *arg)
{
    func_02065504((char *) arg + 0x24);
}

void func_020653d0(UnkStruct_020653d0 *param)
{
    switch (param->unk_14) {
        case 1:
            func_020653b0((UnkStruct_020653b0 *) param);
            break;
        case 2:
            func_02065354((UnkStruct_02065354 *) param);
            break;
    }
}

void func_020653b0(UnkStruct_020653b0 *s)
{
    s->unk_04 = 0;
    s->unk_14 = 2;
    s->unk_1C = 0;
    s->unk_20 = 0x800;
    s->unk_18 = 0;
    func_020654d8((char *) s + 0x24, 0, (void *) 0xB4);
}

void func_02065354(UnkStruct_02065354 *p)
{
    int v;

    p->unk_08 = 0;
    p->unk_0C = -0x1000;
    p->unk_10 = 0;
    p->unk_1C += p->unk_20;

    if (p->unk_18 == 0) {
        if (p->unk_1C >= 0x1000) {
            p->unk_1C = 0x1000;
            p->unk_20 = -0x333;
            p->unk_18 = 1;
        }
    } else {
        if (p->unk_1C < 0) {
            p->unk_1C = 0;
            p->unk_20 = 0;
            p->unk_00 = 9;
            p->unk_14 = 0;
        }
    }

    v = (9 * p->unk_1C) >> 12;
    p->unk_04 = (unsigned short) ((v << 10) | ((v << 5) | v));
}

void func_02065334(void *param)
{
    switch (*(int *) ((char *) param + 0x14)) {
        case 1:
            func_0206531c((struct UnkStruct_0206531c *) param);
            break;
        case 2:
            func_02065284((UnkStruct_02065284 *) param);
            break;
    }
}

void func_0206531c(struct UnkStruct_0206531c *p)
{
    p->unk_04 = 0;
    p->unk_14 = 2;
    p->unk_1C = 0;
    p->unk_20 = 0x548;
    p->unk_18 = 0;
}

void func_02065284(UnkStruct_02065284 *obj)
{
    int scale, val, c, l, m;

    obj->unk_08 = 0;
    obj->unk_0C = -4096;
    obj->unk_10 = 0;
    obj->unk_1C += obj->unk_20;

    if (obj->unk_18 == 0) {
        if (obj->unk_1C >= 0x1000) {
            obj->unk_1C = 0x1000;
            obj->unk_20 = -614;
            obj->unk_18 = 1;
        }
    } else {
        if (obj->unk_1C < 0) {
            obj->unk_1C = 0;
            obj->unk_00 = 9;
            obj->unk_14 = 0;
        }
    }

    if (obj->unk_00 != 9) {
        scale = obj->unk_1C;
        val = data_020ccb98[obj->unk_00 - 1];
        c = ((((val & 0x7c00) >> 10) * scale) >> 12) << 10;
        l = ((val & 0x1f) * scale) >> 12;
        m = ((((val & 0x3e0) >> 5) * scale) >> 12) << 5;
        obj->unk_04 = (unsigned short) (c | (l | m));
    }
}

void func_02065268(int val)
{
    unsigned int base = data_021cd864;
    if (base != 0) {
        int *p = (int *) (base + 0x124);
        *p = val;
        p[5] = 1;
    }
}

int func_0206521c(unsigned char *out, int type)
{
    int changed = 0;
    switch (type) {
        case 3:
        case 4:
            if (*out != data_021cd87c.a) {
                *out = data_021cd87c.a;
                *(int *) (out + 4) = data_021cd87c.x;
                *(int *) (out + 0x1c) = data_021cd87c.z;
                changed = 1;
            }
            break;
        case 5:
            if (*out != data_021cd87c.b) {
                *out = data_021cd87c.b;
                *(int *) (out + 4) = data_021cd87c.y;
                *(int *) (out + 0x1c) = data_021cd87c.w;
                changed = 1;
            }
            break;
    }
    return changed;
}

void func_02065218(void *receiver) {}

short func_020651b0(void *param)
{
    Pair out;
    Pair p2;
    Pair p1;

    p2.raw = *(u16 *) ((u8 *) param + 8);
    func_0209def4(&p1.raw);
    func_0209ddd4(p1, p2, &out);
    return (short) -(int) (((int) ((out.unk_00.a + out.unk_00.b * 0x3c) << 0xf) / 0x5a0) - 0x4000);
}

void func_0206515c(int *arg1, int *arg2)
{
    if (func_020ea838(arg1) != 0) {
        if (VEC_Mag(arg1) >= 0xff0) {
            arg1[0] = FX_MulFunc(arg1[0], 0xff0);
            arg1[1] = FX_MulFunc(arg1[1], 0xff0);
            arg1[2] = FX_MulFunc(arg1[2], 0xff0);
        }
    }
    if (arg2 != 0) {
        arg2[0] = arg1[0];
        arg2[1] = arg1[1];
        arg2[2] = arg1[2];
    }
}

void func_02065110(UnkStruct_02065110 *self, int other)
{
    switch (self->type) {
        case 0:
        case 1:
        case 2:
            func_020ea78c((void *) other, self->unk_10);
            func_020ea6e0(other, (int) func_020651b0((void *) self));
            break;
        default:
            func_020ea78c((void *) other, self->unk_10);
            func_020ea6e0(other, self->unk_12);
            break;
    }
}
