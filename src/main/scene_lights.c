/* scene_lights: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020650ac @ 0x020650ac, 0x64 bytes, Thumb
 * func_02065020 @ 0x02065020, 0x8c bytes, Thumb
 * func_02064fb4 @ 0x02064fb4, 0x6c bytes, Thumb
 * func_02064f84 @ 0x02064f84, 0x2e bytes, Thumb
 * func_02064ef8 @ 0x02064ef8, 0x8c bytes, Thumb
 * func_02064e28 @ 0x02064e28, 0xd0 bytes, Thumb
 * func_02064ddc @ 0x02064ddc, 0x4c bytes, Thumb
 * func_02064db8 @ 0x02064db8, 0x24 bytes, Thumb
 * func_02064da0 @ 0x02064da0, 0x18 bytes, Thumb
 * func_02064d8c @ 0x02064d8c, 0x12 bytes, Thumb
 * func_02064d50 @ 0x02064d50, 0x3c bytes, Thumb
 * func_02064d1c @ 0x02064d1c, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} LocalData;

typedef struct {
    u32 pad_00[3];
    u32 unk_0C;
    unsigned char pad_10[0x24];
    u16 unk_34;
    u16 pad_36;
    LocalData sub;
} UnkStruct_020650ac;

struct GlobalData {
    unsigned char pad_00[0x16a];
    unsigned short unk_16A;
    unsigned short unk_16C;
};

struct Arg {
    unsigned char pad_00[0x14];
    unsigned char flag;
    unsigned char pad_15[3];
    unsigned int mode;
    unsigned char pad_1C[0x18];
    unsigned short result;
};

// Bitfield reads (RGB555).
typedef struct Rgb {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 x : 1;
} Rgb;

typedef struct UnkStruct_02064fb4 {
    u8 pad_00[0x16a];
    Rgb c0;
    Rgb c1;
} UnkStruct_02064fb4;

typedef struct UnkStruct_02064fb4_2 {
    u8 pad_00[0x1c];
    u8 unk_1C[0x18];
    u16 unk_34;
} UnkStruct_02064fb4_2;

typedef struct {
    int x, y, z;
} Position;

typedef struct {
    int type;
    int unk_04[2];
    int unk_0C;
    unsigned char pad_10[0x24];
    unsigned short dir;
    unsigned char pad_36[2];
    int sub38;
} UnkStruct_02064ef8;

typedef struct {
    int unk_00;
    unsigned char pad_04[0x14 - 4];
    unsigned char unk_14;
    unsigned char pad_15[3];
    int unk_18;
    unsigned char unk_1C[0x30 - 0x1c];
    int unk_30;
} UnkStruct_02064e28;

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
} UnkStruct_02064e28_2;

struct UnkStruct_02064ddc {
    unsigned char pad_00[4];
    void *unk_04;
    unsigned char pad_08[0x34 - 0x8];
    unsigned short unk_34;
    unsigned char pad_36[0x38 - 0x36];
    int unk_38;
    int unk_3C;
    int unk_40;
};

struct UnkStruct_02064d50 {
    char data[0x44];
};

struct Main {
    void *vtable;
    char pad_04[0x54];
    struct UnkStruct_02064d50 sub;
};

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x54];
} UnkStruct_02064d1c;

extern int data_021c67a4;
extern void func_02065110(UnkStruct_020650ac *obj, LocalData *data);
extern int func_0203c590(int value);
extern void func_020ea78c(LocalData *data, int value);
extern int func_020bbf00(int value);
extern void func_0206515c(LocalData *src, LocalData *dst);
extern int func_020b3658(void *p);
extern struct GlobalData *data_021cd864;
extern int func_0206521c(unsigned char *p, int v);
extern int func_020b3670(void *p, int a, int b, int c, int d);
extern void func_020b36c8(void *p);
extern void G3_MultMtx33(void *p);
extern void NNS_G3dGlbLightVector(void *p, short a, short b, short c);
extern void NNS_G3dGlbLightColor(void *p, unsigned short d);
extern unsigned char data_021cd87c[];
extern int data_021cd888[];
extern int data_021cd880[];
extern void func_020b373c(void *);
extern char data_020de710[];
extern char data_020da13c[];
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);

void func_020650ac(UnkStruct_020650ac *obj)
{
    volatile u16 t1, t2;
    LocalData local1;
    LocalData local2;
    LocalData *dst;
    int ret;

    local1.a = 0;
    local1.b = 0;
    local1.c = 0xfffff000;

    func_02065110(obj, &local1);

    if (data_021c67a4) {
        ret = func_0203c590(data_021c67a4);
        func_020ea78c(&local1, ret);
    }

    t1 = (u16) func_020bbf00(obj->unk_0C);
    t2 = t1;
    obj->unk_34 = t2;

    local2.a = local1.a;
    local2.b = local1.b;
    local2.c = local1.c;

    dst = &obj->sub;
    func_0206515c(&local2, dst);
}

void func_02065020(struct Arg *arg)
{
    int t;
    struct GlobalData *g;
    unsigned short raw1;
    unsigned int lm;
    unsigned short raw2;
    int low;
    int mid;
    int high;
    unsigned int low1;
    unsigned int low2;
    unsigned int mid1;
    unsigned int mid2;
    unsigned int high1;
    unsigned int high2;
    t = func_020b3658(((char *) arg) + 0x1c);
    g = data_021cd864;
    raw1 = g->unk_16C;
    raw2 = g->unk_16A;
    low1 = ((unsigned int) (raw1 << 27)) >> 27;
    low2 = ((unsigned int) (raw2 << 27)) >> 27;
    low = low1 + ((((int) (low2 - low1)) * t) >> 12);
    mid1 = ((unsigned int) (raw1 << 22)) >> 27;
    mid2 = ((unsigned int) (raw2 << 22)) >> 27;
    mid = mid1 + ((((int) (mid2 - mid1)) * t) >> 12);
    high1 = ((unsigned int) (raw1 << 17)) >> 27;
    high2 = ((unsigned int) (raw2 << 17)) >> 27;
    high = high1 + ((((int) (high2 - high1)) * t) >> 12);
    if (arg->flag == 0) {
        if (arg->mode != 0) {
            low = 0;
            mid = 0;
            high = 0;
        }
    } else if (arg->mode == 2) {
        low = 16;
        mid = 16;
        high = 13;
    }
    lm = low | (mid << 5);
    arg->result = (high << 10) | lm;
}

void func_02064fb4(UnkStruct_02064fb4_2 *self)
{
    int t;

    t = func_020b3658(self->unk_1C);
    // Red and green are combined first, then blue.
    self->unk_34 =
        (u16) ((((*(UnkStruct_02064fb4 **) &data_021cd864)->c1.b +
                 ((((*(UnkStruct_02064fb4 **) &data_021cd864)->c0.b - (*(UnkStruct_02064fb4 **) &data_021cd864)->c1.b) * t) >>
                  12))
                << 10) |
               (((*(UnkStruct_02064fb4 **) &data_021cd864)->c1.r +
                 ((((*(UnkStruct_02064fb4 **) &data_021cd864)->c0.r - (*(UnkStruct_02064fb4 **) &data_021cd864)->c1.r) * t) >>
                  12)) |
                (((*(UnkStruct_02064fb4 **) &data_021cd864)->c1.g +
                  ((((*(UnkStruct_02064fb4 **) &data_021cd864)->c0.g - (*(UnkStruct_02064fb4 **) &data_021cd864)->c1.g) * t) >>
                   12))
                 << 5)));
}

void func_02064f84(void *arg)
{
    int f = func_020b3658((char *) arg + 0x1c);
    int a = ((f << 4) >> 12) + 15;
    int b = ((f << 2) >> 12) + 25;
    int c = ((9 * f) >> 12) + 20;
    *(unsigned short *) ((char *) arg + 0x34) = (unsigned short) ((a << 10) | (b | (c << 5)));
}

void func_02064ef8(UnkStruct_02064ef8 *self)
{
    volatile unsigned short buf[2];
    Position local;
    Position copy;

    switch (self->type) {
        case 3:
            func_02065020((struct Arg *) self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        case 4:
            func_02064fb4((UnkStruct_02064fb4_2 *) self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        case 5:
            func_02064f84((void *) self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        default:
            buf[0] = (unsigned short) func_020bbf00(self->unk_0C);
            buf[1] = buf[0];
            self->dir = buf[1];
            local.x = 0;
            local.y = 0;
            local.z = -0x1000;
            break;
    }

    func_02065110((UnkStruct_020650ac *) self, (LocalData *) (&local));
    copy.x = local.x;
    copy.y = local.y;
    copy.z = local.z;
    func_0206515c((LocalData *) (&copy), (LocalData *) (&self->sub38));
}

void func_02064e28(UnkStruct_02064e28 *s)
{
    if ((*(UnkStruct_02064e28_2 **) &data_021cd864)->unk_50 == 0) {
        func_020650ac((UnkStruct_020650ac *) s);
        return;
    }
    if (func_0206521c(&s->unk_14, s->unk_00) != 0) {
        if (s->unk_14 != 0) {
            switch (s->unk_18) {
                case 0:
                case 3:
                    func_020b3670(&s->unk_1C, 1, 1, 0, 0x1000 / s->unk_30);
                    break;
                case 1:
                    func_020b3670(&s->unk_1C, 1, 1, 1, 0x800);
                    break;
                default:
                    func_020b3670(&s->unk_1C, 1, 0, 0, 0x800);
                    break;
            }
        } else {
            switch (s->unk_18) {
                case 0:
                case 3:
                    func_020b3670(&s->unk_1C, 0, 1, 0, 0x1000 / s->unk_30);
                    break;
                default:
                    func_020b3670(&s->unk_1C, 0, 0, 0, 0x800);
                    break;
            }
        }
    }
    func_020b36c8(&s->unk_1C);
    func_02064ef8((UnkStruct_02064ef8 *) s);
}

void func_02064ddc(struct UnkStruct_02064ddc *s, void *arg)
{
    void *obj = s->unk_04;
    *(volatile unsigned int *) 0x04000440 = 2;
    *(volatile unsigned int *) 0x04000454 = 0;
    G3_MultMtx33(arg);
    NNS_G3dGlbLightVector(obj, (short) s->unk_38, (short) s->unk_3C, (short) s->unk_40);
    NNS_G3dGlbLightColor(obj, s->unk_34);
}

void func_02064db8(int index, int value1, int value2)
{
    data_021cd87c[index] = 1;
    data_021cd888[index] = value1;
    data_021cd880[index] = value2;
}

void func_02064da0(unsigned int idx, unsigned int value)
{
    data_021cd87c[idx] = 0;
    ((unsigned int *) data_021cd888)[idx] = value;
}

void *func_02064d8c(void *arg)
{
    func_020b373c((char *) arg + 0x1c);
    return arg;
}

void *func_02064d50(void *arg)
{
    struct Main *self = (struct Main *) arg;
    self->vtable = (void *) data_020de710;
    __cxa_vec_cleanup((void *) (&self->sub), 3, 0x44, (((void (*)(void *)) func_02064d8c)));
    self->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

UnkStruct_02064d1c *func_02064d1c(UnkStruct_02064d1c *self)
{
    self->unk_00 = ((char *) data_020de710);
    __cxa_vec_cleanup((void *) ((char *) self + 0x58), 3, 0x44, (((void (*)(void *)) func_02064d8c)));
    self->unk_00 = ((char *) data_020da13c);
    func_020ee62c((void *) self);
    return self;
}
