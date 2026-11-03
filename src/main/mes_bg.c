/* mes_bg: 40 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aca94 @ 0x020aca94, 0x4 bytes, Thumb
 * func_020aca80 @ 0x020aca80, 0x14 bytes, Thumb
 * func_020aca7c @ 0x020aca7c, 0x4 bytes, Thumb
 * func_020aca74 @ 0x020aca74, 0x8 bytes, Thumb
 * func_020aca70 @ 0x020aca70, 0x4 bytes, Thumb
 * func_020aca6c @ 0x020aca6c, 0x4 bytes, Thumb
 * func_020aca60 @ 0x020aca60, 0xc bytes, Thumb
 * func_020aca54 @ 0x020aca54, 0xc bytes, Thumb
 * func_020aca48 @ 0x020aca48, 0xc bytes, Thumb
 * func_020aca3c @ 0x020aca3c, 0xc bytes, Thumb
 * func_020aca30 @ 0x020aca30, 0xc bytes, Thumb
 * func_020aca24 @ 0x020aca24, 0xc bytes, Thumb
 * func_020aca04 @ 0x020aca04, 0x20 bytes, Thumb
 * func_020ac9ec @ 0x020ac9ec, 0x18 bytes, Thumb
 * func_020ac9cc @ 0x020ac9cc, 0x20 bytes, Thumb
 * func_020ac9a4 @ 0x020ac9a4, 0x28 bytes, Thumb
 * func_020ac98c @ 0x020ac98c, 0x18 bytes, Thumb
 * func_020ac96c @ 0x020ac96c, 0x20 bytes, Thumb
 * func_020ac954 @ 0x020ac954, 0x18 bytes, Thumb
 * func_020ac8f0 @ 0x020ac8f0, 0x64 bytes, Thumb
 * func_020ac8c8 @ 0x020ac8c8, 0x26 bytes, Thumb
 * func_020ac8a8 @ 0x020ac8a8, 0x20 bytes, Thumb
 * func_020ac89c @ 0x020ac89c, 0xc bytes, Thumb
 * func_020ac71c @ 0x020ac71c, 0x180 bytes, Thumb
 * func_020ac624 @ 0x020ac624, 0xf8 bytes, Thumb
 * func_020ac588 @ 0x020ac588, 0x9c bytes, Thumb
 * func_020ac50c @ 0x020ac50c, 0x7c bytes, Thumb
 * func_020ac4ec @ 0x020ac4ec, 0x1e bytes, Thumb
 * func_020ac478 @ 0x020ac478, 0x72 bytes, Thumb
 * func_020ac470 @ 0x020ac470, 0x8 bytes, Thumb
 * func_020ac46c @ 0x020ac46c, 0x4 bytes, Thumb
 * func_020ac444 @ 0x020ac444, 0x28 bytes, Thumb
 * func_020ac424 @ 0x020ac424, 0x20 bytes, Thumb
 * func_020ac3f8 @ 0x020ac3f8, 0x2a bytes, Thumb
 * func_020ac3ec @ 0x020ac3ec, 0xc bytes, Thumb
 * func_020ac3e0 @ 0x020ac3e0, 0xc bytes, Thumb
 * func_020ac39c @ 0x020ac39c, 0x44 bytes, Thumb
 * func_020ac384 @ 0x020ac384, 0x16 bytes, Thumb
 * func_020ac358 @ 0x020ac358, 0x2c bytes, Thumb
 * func_020ac318 @ 0x020ac318, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
} UnkStruct_020ac9cc;

typedef struct {
    void *data;
    int unk_04;
    short arr[5];
    char unk_12;
    int unk_14;
    short unk_18;
    short unk_1A;
    short unk_1C;
    short unk_1E;
} Func_020ac9a4_struct;

struct Struct020ac98c {
    unsigned char *unk_00;
};

struct UnkStruct_020ac954 {
    void *unk_00;
};

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_020ac8f0;

typedef struct {
    unsigned char pad_00[4];
    unsigned char *p;
    unsigned char pad_08[0x16];
    unsigned short unk_1E;
} UnkStruct_020ac624;

typedef struct UnkStruct_020ac588 {
    u32 pad_00;        // 0x00
    char *base;        // 0x04
    char pad_08[0x16]; // 0x08..0x1d
    u16 unk_1E;        // 0x1e
} UnkStruct_020ac588;

typedef struct {
    unsigned int pad_00;
    unsigned char *data;
    unsigned char pad_08[0x1e - 0x08];
    unsigned short unk_1E;
} UnkStruct_020ac50c;

typedef struct {
    char pad_00[4];
    unsigned char *unk_04;
    char pad_08[0xc];
    unsigned int unk_14;
} UnkStruct_020ac478;

typedef struct {
    unsigned int pad_00;
    unsigned int data;
} UnkStruct_020ac424;

struct func_020ac39c_ctx {
    unsigned char pad_00[0x14];
    int unk_14;
    u16 unk_18;
    u16 unk_1A;
};

typedef struct {
    char pad_00[8];
    unsigned short arr[5];
    unsigned char flag;
} UnkStruct_020ac384;

typedef struct {
    unsigned char pad_00[8];
    unsigned short arr[5];
    unsigned char flag;
} Func020ac358Data;

extern void func_0208e9e0(char *ptr, int b, int c);
extern int func_0208e930(void *);
extern void *func_0208e95c(int a, int b);
extern void *func_0208e8d4(void *obj, int arg);
extern unsigned int data_020e4030;
extern void *func_0208e7f0(void *obj);
extern void func_020edb3c(UnkStruct_020ac9cc *p);
extern char data_020e3fb4;
extern int FS_OpenFile(const void *, const void *);
extern void *func_020e98d4(int);
extern int FS_ReadFile(const void *, void *, int);
extern int FS_CloseFile(const void *);
extern int data_020e40c4;
extern __arm void FS_InitFile(void *buffer);
extern int data_021fbe94;
extern void func_020e993c(int arg1, int arg2);
extern void MI_CpuFill8(int, int, int);
extern void MI_CpuCopy8(void *dst, void *src, int n);
extern void DC_FlushRange(unsigned int a, unsigned int b);
extern void func_02113088(unsigned int a, unsigned int b, unsigned int c);
extern void GX_LoadBGPltt(void *ptr, int value, int count);
extern void func_02001b44(int);
extern void func_02001b34(int);
extern int func_0209d368(int id, int index);
extern void func_02001e74(int, int);
extern unsigned char data_020d1dd4[];
extern unsigned char data_020d1dd8[];
extern unsigned char data_020d1ddc[];

void func_020ac8a8(int *param);
void func_020ac478(UnkStruct_020ac478 *self, unsigned int idx, unsigned int count);
void func_020ac470(unsigned short *p0, int p1);

void func_020aca94(int *p0, int p1)
{
    p0[3] = p1;
}

int func_020aca80(void *arg0)
{
    int val;
    int val2;

    val = *(int *) ((char *) arg0 + 0xc);
    val2 = val - 0x1000;
    val2 = val2 << 5;
    val2 = -val2;
    return val2 >> 0xc;
}

int func_020aca7c(void *object)
{
    return 6;
}

int func_020aca74(void *argument0)
{
    return func_020aca80((void *) argument0);
}

int func_020aca70(void *object)
{
    return 32;
}

int func_020aca6c(void *object)
{
    return 0;
}

void func_020aca60(char *ptr, int b, int c)
{
    func_0208e9e0(ptr + 0x10, b, c);
}

int func_020aca54(void *arg)
{
    return func_0208e930((char *) arg + 0x10);
}

void func_020aca48(void *ptr)
{
    func_0208e95c((int) ((char *) ptr + 0x10), 1);
}

void func_020aca3c(int a)
{
    func_0208e95c(a + 0x10, 0);
}

void func_020aca30(int a)
{
    func_0208e95c(a + 0x10, 2);
}

void func_020aca24(unsigned char *param)
{
    func_0208e95c((int) (param + 0x10), 3);
}

void *func_020aca04(void *param)
{
    func_0208e8d4(param, 1);
    *(unsigned int *) param = (unsigned int) &data_020e4030;
    *((int *) ((char *) param + 0x28)) = 0;
    return param;
}

void *func_020ac9ec(void *obj)
{
    *(void **) obj = ((char *) &data_020e4030);
    func_0208e7f0(obj);
    return obj;
}

UnkStruct_020ac9cc *func_020ac9cc(UnkStruct_020ac9cc *p)
{
    p->unk_00 = (unsigned int) &data_020e4030;
    func_0208e7f0((void *) p);
    func_020edb3c(p);
    return p;
}

void func_020ac9a4(Func_020ac9a4_struct *p)
{
    unsigned int i;

    p->data = ((int *) &data_020e3fb4);
    p->unk_04 = 0;
    p->unk_12 = 0;
    p->unk_14 = 0;
    p->unk_18 = 0;
    p->unk_1A = 0;
    p->unk_1C = 0;
    p->unk_1E = 0;

    i = 0;
    do {
        p->arr[i] = 0;
        i++;
    } while (i < 5);
}

void *func_020ac98c(struct Struct020ac98c *self)
{
    self->unk_00 = ((unsigned char *) &data_020e3fb4);
    func_020ac8a8((int *) self);
    return self;
}

void *func_020ac96c(void *p)
{
    *(void **) p = (void *) &data_020e3fb4;
    func_020ac8a8((int *) p);
    func_020edb3c((UnkStruct_020ac9cc *) p);
    return p;
}

struct UnkStruct_020ac954 *func_020ac954(struct UnkStruct_020ac954 *self)
{
    self->unk_00 = &data_020e3fb4;
    func_020ac8a8((int *) self);
    return self;
}

int func_020ac8f0(UnkStruct_020ac8f0 *out, const void *param1)
{
    int a;
    int b;
    int c;

    a = FS_OpenFile(param1, &data_020e40c4);
    out->unk_04 = func_020e98d4(0x800);

    if (out->unk_04 != 0) {
        b = FS_ReadFile(param1, out->unk_04, 0x800) != -1;
    } else {
        b = 0;
    }

    c = FS_CloseFile(param1);

    return (a && b && c && out->unk_04 != 0) ? 1 : 0;
}

int func_020ac8c8(void *param)
{
    unsigned char buffer[0x4c];
    int result = 0;

    FS_InitFile(buffer);
    if (func_020ac8f0((UnkStruct_020ac8f0 *) param, (const void *) buffer) != 0) {
        result = 1;
    }
    return result;
}

void func_020ac8a8(int *param)
{
    if (param[1] != 0) {
        func_020e993c(data_021fbe94, param[1]);
        param[1] = 0;
    }
}

void func_020ac89c(int a, int b)
{
    MI_CpuFill8(a, 0x10, b);
}

void func_020ac71c(char *self)
{
    MI_CpuCopy8(*(char **) (self + 4) + 0x2a2, *(char **) (self + 4) + 0x3a2, 0x1a);
    MI_CpuCopy8(*(char **) (self + 4) + 0x2e2, *(char **) (self + 4) + 0x3e2, 0x1a);
    MI_CpuCopy8(*(char **) (self + 4) + 0x25e, *(char **) (self + 4) + 0x35e, 0x22);
    MI_CpuCopy8(*(char **) (self + 4) + 0x51e, *(char **) (self + 4) + 0x41e, 0x22);

    *(unsigned short *) (*(char **) (self + 4) + 0x39e) = *(unsigned short *) (*(char **) (self + 4) + 0x29e);
    *(unsigned short *) (*(char **) (self + 4) + 0x3a0) = *(unsigned short *) (*(char **) (self + 4) + 0x2a0);
    *(unsigned short *) (*(char **) (self + 4) + 0x3be) = *(unsigned short *) (*(char **) (self + 4) + 0x2be);
    *(unsigned short *) (*(char **) (self + 4) + 0x3bc) = *(unsigned short *) (*(char **) (self + 4) + 0x2bc);
    *(unsigned short *) (*(char **) (self + 4) + 0x3de) = *(unsigned short *) (*(char **) (self + 4) + 0x4de);
    *(unsigned short *) (*(char **) (self + 4) + 0x3e0) = *(unsigned short *) (*(char **) (self + 4) + 0x4e0);
    *(unsigned short *) (*(char **) (self + 4) + 0x3fe) = *(unsigned short *) (*(char **) (self + 4) + 0x4fe);
    *(unsigned short *) (*(char **) (self + 4) + 0x3fc) = *(unsigned short *) (*(char **) (self + 4) + 0x4fc);

    func_020ac89c((int) (*(char **) (self + 4) + 0x25e), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x29e), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x2de), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x31e), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x45e), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x49e), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x4de), 0x22);
    func_020ac89c((int) (*(char **) (self + 4) + 0x51e), 0x22);

    func_020ac478((UnkStruct_020ac478 *) self, 0xd, 0x10);
    func_020ac470((unsigned short *) self, 0xd);
    *(unsigned short *) (self + 0x1e) = 1;
}

void func_020ac624(UnkStruct_020ac624 *self)
{
    MI_CpuCopy8((void *) (self->p + 0x29e), (void *) (self->p + 0x39e), 0x22);
    MI_CpuCopy8((void *) (self->p + 0x2de), (void *) (self->p + 0x3de), 0x22);
    MI_CpuCopy8((void *) (self->p + 0x25e), (void *) (self->p + 0x35e), 0x22);
    MI_CpuCopy8((void *) (self->p + 0x49e), (void *) (self->p + 0x41e), 0x22);
    MI_CpuCopy8((void *) (self->p + 0x4de), (void *) (self->p + 0x45e), 0x22);
    MI_CpuCopy8((void *) (self->p + 0x51e), (void *) (self->p + 0x49e), 0x22);
    func_020ac89c((int) (self->p + 0x25e), 0x22);
    func_020ac89c((int) (self->p + 0x29e), 0x22);
    func_020ac89c((int) (self->p + 0x2de), 0x22);
    func_020ac89c((int) (self->p + 0x31e), 0x22);
    func_020ac89c((int) (self->p + 0x4de), 0x22);
    func_020ac89c((int) (self->p + 0x51e), 0x22);
    func_020ac478((UnkStruct_020ac478 *) self, 0xd, 0x12);
    func_020ac470((unsigned short *) self, 0xd);
    self->unk_1E = 2;
}

void func_020ac588(UnkStruct_020ac588 *self)
{
    MI_CpuCopy8(self->base + 0x29e, (void *) (self->base + 0x39e), 0x22);
    MI_CpuCopy8(self->base + 0x2de, (void *) (self->base + 0x3de), 0x22);
    MI_CpuCopy8(self->base + 0x25e, (void *) (self->base + 0x35e), 0x22);
    func_020ac89c((int) (self->base + 0x25e), 0x22);
    func_020ac89c((int) (self->base + 0x29e), 0x22);
    func_020ac89c((int) (self->base + 0x2de), 0x22);
    func_020ac89c((int) (self->base + 0x31e), 0x22);
    func_020ac478((UnkStruct_020ac478 *) self, 0xd, 0x14);
    func_020ac470((unsigned short *) self, 0xd);
    self->unk_1E = 3;
}

void func_020ac50c(UnkStruct_020ac50c *self)
{
    MI_CpuCopy8(self->data + 0x29e, (void *) (self->data + 0x31e), 0x22);
    MI_CpuCopy8(self->data + 0x2de, (void *) (self->data + 0x35e), 0x22);
    MI_CpuCopy8(self->data + 0x25e, (void *) (self->data + 0x2de), 0x22);
    func_020ac89c((int) (self->data + 0x25e), 0x22);
    func_020ac89c((int) (self->data + 0x29e), 0x22);
    func_020ac478((UnkStruct_020ac478 *) self, 0xb, 0x14);
    func_020ac470((unsigned short *) self, 0xb);
    self->unk_1E = 4;
}

void func_020ac4ec(void *param1)
{
    func_020ac478((UnkStruct_020ac478 *) param1, 9, 0x14);
    func_020ac470((unsigned short *) param1, 9);
    *(unsigned short *) ((char *) param1 + 0x1e) = 5;
}

void func_020ac478(UnkStruct_020ac478 *self, unsigned int idx, unsigned int count)
{
    int a, b, c;
    int j;
    unsigned short v;
    unsigned char *p;

    if (self->unk_14 >= 13) {
        return;
    }
    a = 13 - self->unk_14;
    b = (30 - a) << 1;
    c = (31 - a) << 1;
    while (idx <= count) {
        p = self->unk_04;
        v = *(unsigned short *) (p + idx * 64 + 0x3c);
        *(unsigned short *) ((unsigned int) b + (unsigned int) p + idx * 64) = v;
        p = self->unk_04;
        v = *(unsigned short *) (p + idx * 64 + 0x3e);
        *(unsigned short *) ((unsigned int) c + (unsigned int) p + idx * 64) = v;
        j = a - 1;
        while (j >= 0) {
            func_020ac89c((int) (self->unk_04 + idx * 64 + (31 - j) * 2), 2);
            j--;
        }
        idx++;
    }
}

void func_020ac470(unsigned short *p0, int p1)
{
    p0[14] = (((int) (p1) - (9)) << 3);
}

void func_020ac46c(int *p0, int p1)
{
    p0[5] = p1;
}

void func_020ac444(void *receiver)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000A;

    *reg &= ~3;
    *reg = (*reg & 0x43) | 0x500;
    *reg &= ~0x40;
}

void func_020ac424(UnkStruct_020ac424 *p)
{
    DC_FlushRange(p->data, 0x800);
    func_02113088(p->data, 0, 0x800);
}

void func_020ac3f8(void *param)
{
    unsigned char *p = (unsigned char *) param;
    if (p[0x12] != 0) {
        DC_FlushRange((unsigned int) (p + 8), 10);
        GX_LoadBGPltt(p + 8, 0x82, 10);
        p[0x12] = 0;
    }
}

void func_020ac3ec(void *receiver)
{
    func_02001b44(2);
}

void func_020ac3e0(void *object)
{
    func_02001b34(2);
}

void func_020ac39c(struct func_020ac39c_ctx *p, int x, int y)
{
    int a, b, c, r;

    a = func_0209d368(0x66, 2);
    b = func_0209d368(0x66, 3) - 8;
    c = 13 - p->unk_14;

    if (c < 0) {
        c = 0;
    }
    r = x + (a + b * c);
    func_02001e74(r, y);
    p->unk_18 = r;
    p->unk_1A = y;
}

void func_020ac384(UnkStruct_020ac384 *s)
{
    int i;
    for (i = 0; i < 5; i++) {
        s->arr[i] = 12;
    }
    s->flag = 1;
}

void func_020ac358(Func020ac358Data *data, int index, unsigned short value)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (i == index) {
            data->arr[i] = value;
        } else {
            data->arr[i] = 0;
        }
    }
    data->flag = 1;
}

int func_020ac318(int r0, int r1)
{
    int result;

    result = 0;
    if (r1 == 1) {
    } else if (r1 == 2) {
        result = data_020d1dd4[r0];
    } else if (r1 == 3) {
        result = data_020d1dd8[r0];
    } else if (r1 == 4) {
        result = data_020d1ddc[r0];
    } else if (r1 == 5) {
        result = r0;
    }
    return result * 26 + 153;
}
