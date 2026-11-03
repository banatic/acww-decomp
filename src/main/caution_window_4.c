/* caution_window_4: 32 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02038d50 @ 0x02038d50, 0x24 bytes, Thumb
 * func_02038d30 @ 0x02038d30, 0x20 bytes, Thumb
 * func_02038d18 @ 0x02038d18, 0x18 bytes, Thumb
 * func_02038cf8 @ 0x02038cf8, 0x20 bytes, Thumb
 * func_02038cf0 @ 0x02038cf0, 0x8 bytes, Thumb
 * func_02038cec @ 0x02038cec, 0x4 bytes, Thumb
 * func_02038ccc @ 0x02038ccc, 0x20 bytes, Thumb
 * func_02038cb4 @ 0x02038cb4, 0x18 bytes, Thumb
 * func_02038c94 @ 0x02038c94, 0x20 bytes, Thumb
 * func_02038c90 @ 0x02038c90, 0x4 bytes, Thumb
 * func_02038c8c @ 0x02038c8c, 0x4 bytes, Thumb
 * func_02038c6c @ 0x02038c6c, 0x20 bytes, Thumb
 * func_02038c54 @ 0x02038c54, 0x18 bytes, Thumb
 * func_02038c34 @ 0x02038c34, 0x20 bytes, Thumb
 * func_02038c30 @ 0x02038c30, 0x4 bytes, Thumb
 * func_02038c2c @ 0x02038c2c, 0x4 bytes, Thumb
 * func_02038bfc @ 0x02038bfc, 0x30 bytes, Thumb
 * func_02038bac @ 0x02038bac, 0x50 bytes, Thumb
 * func_02038b80 @ 0x02038b80, 0x2c bytes, Thumb
 * func_02038acc @ 0x02038acc, 0xb4 bytes, Thumb
 * func_02038a90 @ 0x02038a90, 0x3c bytes, Thumb
 * func_02038a50 @ 0x02038a50, 0x40 bytes, Thumb
 * func_02038a44 @ 0x02038a44, 0xc bytes, Thumb
 * func_02038a30 @ 0x02038a30, 0x14 bytes, Thumb
 * func_02038a20 @ 0x02038a20, 0x10 bytes, Thumb
 * func_02038a10 @ 0x02038a10, 0x10 bytes, Thumb
 * func_02038a00 @ 0x02038a00, 0x10 bytes, Thumb
 * func_020389f0 @ 0x020389f0, 0x10 bytes, Thumb
 * func_020389e0 @ 0x020389e0, 0x10 bytes, Thumb
 * func_02038998 @ 0x02038998, 0x48 bytes, Thumb
 * func_02038910 @ 0x02038910, 0x88 bytes, Thumb
 * func_020388f0 @ 0x020388f0, 0x1e bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02038c94 {
    void *unk_00;
};

struct UnkStruct_02038c6c {
    void *unk_00;
};

typedef struct {
    void *unk_00;
} UnkStruct02038c54;

typedef struct {
    void *unk_00;
    char pad_04[0xa0 - 0x4];
    char pad_A0[0xbc - 0xa0];
    u32 unk_BC;
    u32 unk_C0;
    u32 unk_C4;
    u8 unk_C8;
    u8 unk_C9;
    u8 unk_CA;
    u8 unk_CB;
    u16 unk_CC;
    u16 unk_CE;
    u32 unk_D0;
    u32 unk_D4;
    u32 unk_D8;
    u32 unk_DC;
    u32 unk_E0;
    u32 unk_E4;
    char pad_E8[0x2e8 - 0xe8];
} UnkStruct_02038acc;

typedef struct UnkStruct_02038a50 {
    void *unk_00;
    unsigned char unk_04[0xe4];
    unsigned char unk_E8[0x114];
    unsigned char unk_1FC[0x54];
    unsigned char unk_250[1];
} UnkStruct_02038a50;

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
} UnkStruct_02038a30;

typedef struct {
    unsigned char pad_00[0xc4];
    int unk_C4;
    unsigned char unk_C8;
} UnkStruct_02038910;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short value;
} OtherStruct;

typedef struct {
    char pad_00[0xBC];
    int unk_BC;
} UnkStruct_020388f0;

extern int func_020732c0(void *p);
extern void func_020732cc(void *p, int x);
extern void *data_020ccf94;
extern int data_020da530;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);
extern void *func_020a8cac(void *obj);
extern void func_020a8c1c(void *obj);
extern unsigned char data_020da560[];
extern int data_020da548;
extern int func_020eba08(void);
extern int func_020ec1e8(void);
extern int data_021c5938;
extern unsigned char data_021c5934;
extern signed char data_020ca0f4[0x18];
extern signed char data_020ca10c[][2];
extern int func_02064328(void *dest, const void *src, unsigned int size);
extern char data_020da590[];
extern char data_021c5970;
extern void *func_0205577c(void *);
extern void *func_020ba01c(void *);
extern void MI_CpuFill8(void *, unsigned int, unsigned int);
extern void *func_02055764(void *ptr);
extern unsigned char data_020da520[];
extern unsigned char data_021c5d0c[11];
extern UnkStruct_02038a30 data_021c5ccc;
extern unsigned char data_021c5c4c[];
extern void func_02038828(int, int);
extern void func_02038758(void *p);
extern void func_020386fc(void *arg);
extern int func_020b4980(void *p0, void *p1, int p2);
extern unsigned char data_021c59d0[];
extern unsigned char data_021c5a24[];
extern unsigned char data_021c5b38[];
extern unsigned char data_020e54a8;
extern OtherStruct *data_021f42f4;
extern char data_020da570[];
extern void func_02038424(UnkStruct_02038910 *self);
extern int func_0205556c(void *buf, unsigned int fourcc, void *data);
extern void func_020386c4(UnkStruct_02038910 *self);
extern void func_020382b8(UnkStruct_02038910 *self);
extern void func_020382d4(UnkStruct_02038910 *self);
extern int func_02055454(void *arg);

void func_02038910(UnkStruct_02038910 *self);
void func_020388f0(UnkStruct_020388f0 *self);

void func_02038d50(void)
{
    void *p = data_020ccf94;
    int arg = func_020732c0(p) | 0x20;
    func_020732cc(p, arg);
}

int func_02038d30(int param)
{
    func_020a8cac((void *) param);
    *(int *) param = (int) &data_020da530;
    func_020a8c1c((void *) param);
    return param;
}

void *func_02038d18(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) ((unsigned int *) &data_020da530);
    func_020a8c38(ptr);
    return ptr;
}

void *func_02038cf8(void *self)
{
    *(int *) self = (int) &data_020da530;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_02038cf0(void)
{
    return 256;
}

int func_02038cec(int p0)
{
    return ((int) (p0) + (18));
}

void *func_02038ccc(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) data_020da560;
    func_020a8c1c(obj);
    return obj;
}

void *func_02038cb4(void *p)
{
    *(void **) p = (void *) data_020da560;
    func_020a8c38(p);
    return p;
}

void *func_02038c94(void *self)
{
    ((struct UnkStruct_02038c94 *) self)->unk_00 = ((char *) data_020da560);
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_02038c90(void)
{
    return 64;
}

int func_02038c8c(int p0)
{
    return ((int) (p0) + (18));
}

struct UnkStruct_02038c6c *func_02038c6c(struct UnkStruct_02038c6c *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020da548;
    func_020a8c1c(self);
    return self;
}

void *func_02038c54(void *self)
{
    UnkStruct02038c54 *obj = self;

    obj->unk_00 = &data_020da548;
    func_020a8c38(self);
    return self;
}

void *func_02038c34(void *param)
{
    *(void **) param = ((char *) &data_020da548);
    func_020a8c38(param);
    func_020edb3c(param);
    return param;
}

int func_02038c30(void)
{
    return 128;
}

int func_02038c2c(int p0)
{
    return ((int) (p0) + (18));
}

void func_02038bfc(void)
{
    int a;
    int b;
    int val;

    a = func_020eba08();
    data_021c5938 = a;

    b = func_020ec1e8();

    switch (b) {
        case 3:
        case 4:
            val = 1;
            break;
        default:
            val = 0;
            break;
    }

    data_021c5934 = (unsigned char) val;
}

void func_02038bac(unsigned char *out, signed char *in)
{
    unsigned int c;
    unsigned int i;
    while (*in != 0) {
        c = (unsigned char) *in;
        for (i = 0; i < 0x15; i++) {
            if (c == data_020ca0f4[i]) {
                out[0] = (unsigned char) data_020ca10c[i][0];
                out[1] = (unsigned char) data_020ca10c[i][1];
            }
        }
        in++;
        out += 2;
    }
    out[0] = 0;
    out[1] = 0;
}

char *func_02038b80(void)
{
    char buf[20];
    func_02064328(buf, data_020da590, (*(unsigned int *) &data_021c5938));
    func_02038bac((unsigned char *) (&data_021c5970), (signed char *) buf);
    return &data_021c5970;
}

UnkStruct_02038acc *func_02038acc(UnkStruct_02038acc *self)
{
    self->unk_00 = (void *) ((char *) data_020da520);
    func_0205577c((char *) self + 4);
    func_020ba01c((char *) self + 0xa0);

    self->unk_BC = 0;
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_C9 = 0;
    self->unk_CA = 0;
    self->unk_CB = 0;
    self->unk_CC = 0;
    self->unk_CE = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    self->unk_D8 = 0;
    self->unk_DC = 0;
    self->unk_E0 = 0;
    self->unk_E4 = 0;

    func_02038d30((int) ((char *) self + 0xe8));
    func_02038ccc((char *) self + 0x1fc);
    func_02038c6c((struct UnkStruct_02038c6c *) ((char *) self + 0x250));
    MI_CpuFill8((char *) self + 0x2e4, 0x11, 0x800);

    return self;
}

void *func_02038a90(void *self)
{
    *(void **) self = (void *) data_020da520;
    func_02038c54((void *) ((char *) self + 0x250));
    func_02038cb4((void *) ((char *) self + 0x1FC));
    func_02038d18((void *) ((char *) self + 0xE8));
    func_02055764((void *) ((char *) self + 4));
    return self;
}

UnkStruct_02038a50 *func_02038a50(UnkStruct_02038a50 *self)
{
    self->unk_00 = (void *) data_020da520;
    func_02038c54(self->unk_250);
    func_02038cb4(self->unk_1FC);
    func_02038d18(self->unk_E8);
    func_02055764(self->unk_04);
    func_020edb3c(self);
    return self;
}

unsigned char func_02038a44(void)
{
    return data_021c5d0c[10];
}

int func_02038a30(void)
{
    if (data_021c5ccc.unk_3C >= 5) {
        return 1;
    }
    return 0;
}

void func_02038a20(void)
{
    func_02038910((UnkStruct_02038910 *) ((void *) data_021c5c4c));
}

void func_02038a10(void)
{
    func_020388f0((UnkStruct_020388f0 *) ((void *) data_021c5c4c));
}

void func_02038a00(int p0)
{
    func_02038828((int) ((int *) data_021c5c4c), p0);
}

void func_020389f0(void)
{
    func_02038758((void *) data_021c5c4c);
}

void func_020389e0(void)
{
    func_020386fc((void *) data_021c5c4c);
}

int func_02038998(void)
{
    unsigned char arr[3];
    arr[0] = 0xe3;
    arr[1] = 0xe4;
    arr[2] = 0xe5;
    func_020b4980((void *) data_021c5a24, arr, 0);
    func_020b4980((void *) data_021c59d0, arr + 1, 0);
    return func_020b4980((void *) data_021c5b38, arr + 2, 0);
}

void func_02038910(UnkStruct_02038910 *self)
{
    int flag1 = 1;
    unsigned int b1;
    unsigned int b2;
    int flag2;

    b1 = (data_020e54a8 == 0) ? 1 : 0;
    if (b1 == 0) {
        b2 = (data_020e54a8 == 1) ? 1 : 0;
        if (b2 == 0) {
            flag1 = 0;
        }
    }
    flag2 = (data_021f42f4->value == 5) ? 1 : 0;
    func_02038424(self);
    if (flag1 != 0 || flag2 != 0) {
        func_0205556c((char *) self + 4, 0x43617557, data_020da570);
        func_020386c4(self);
        self->unk_C4 = 0;
        self->unk_C8 = 0;
        func_020382b8(self);
    } else {
        func_020382d4(self);
    }
}

void func_020388f0(UnkStruct_020388f0 *self)
{
    if (self->unk_BC != 0) {
        func_02055454((char *) self + 4);
        self->unk_BC = 0;
    }
}
