/* bmg_file: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9ae8 @ 0x020a9ae8, 0x1a bytes, Thumb
 * func_020a9ae4 @ 0x020a9ae4, 0x4 bytes, Thumb
 * func_020a9ae0 @ 0x020a9ae0, 0x4 bytes, Thumb
 * func_020a9adc @ 0x020a9adc, 0x4 bytes, Thumb
 * func_020a9a90 @ 0x020a9a90, 0x4c bytes, Thumb
 * func_020a9a78 @ 0x020a9a78, 0x18 bytes, Thumb
 * func_020a9a58 @ 0x020a9a58, 0x20 bytes, Thumb
 * func_020a9a40 @ 0x020a9a40, 0x18 bytes, Thumb
 * func_020a9a08 @ 0x020a9a08, 0x36 bytes, Thumb
 * func_020a99d8 @ 0x020a99d8, 0x30 bytes, Thumb
 * func_020a9938 @ 0x020a9938, 0xa0 bytes, Thumb
 * func_020a98e4 @ 0x020a98e4, 0x54 bytes, Thumb
 * func_020a982c @ 0x020a982c, 0xb8 bytes, Thumb
 * func_020a9754 @ 0x020a9754, 0xd8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020a9a90_2 {
    unsigned char data[0x48];
};

struct UnkStruct_020a9a90 {
    void *unk_00;
    unsigned char unk_04;
    unsigned char unk_05[0x3F];
    struct UnkStruct_020a9a90_2 unk_44;
    unsigned char unk_8C;
    unsigned char unk_8D;
    unsigned char pad_8E[0x0E];
    unsigned int unk_9C;
    unsigned int unk_A0;
};

typedef struct {
    unsigned char pad_00[5];
    unsigned char data[62];
    unsigned char pad_43;
    unsigned char unk_44[4];
    unsigned char pad_48[68];
    unsigned char flag;
} UnkStruct_020a9a08;

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[0x88];
    unsigned char unk_8D;
} UnkStruct_020a9938;

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[2];
    unsigned char unk_90[0xc];
    unsigned int unk_9C;
    unsigned int unk_A0;
} UnkStruct_020a98e4;

struct UnkStruct_020a982c {
    u32 unk_00;    // 0x00
    u32 unk_04;    // 0x04
    u32 unk_08;    // 0x08
    u32 unk_0C;    // 0x0c
    u8 unk_10;     // 0x10
    u8 pad_11[11]; // 0x11..0x1b
    u32 unk_1C;    // 0x1c
};

struct GStruct {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned char unk_0E;
    unsigned char pad_0F[5];
};

extern char data_020e3d34;
extern unsigned char data_021f43ec;
extern void FS_InitFile(struct UnkStruct_020a9a90_2 *sub);
extern void MI_CpuFill8(void *s, int c, unsigned int n);
extern void func_020edb3c(void *p);
extern char *strncpy(void *dest, const void *src, unsigned int size);
extern int FS_OpenFile(const void *a, const void *b);
extern int FS_CloseFile(void *ptr);
extern int func_020a9708(void *);
extern int func_020a958c(void *);
extern int func_020a967c(void *);
extern int func_020a9540(void *);
extern unsigned char data_021f446c[0x20];
extern unsigned char data_021f4458[0x14];
extern unsigned char data_021f4428[0xc];
extern u32 data_021f4470; // 0x021f4470
extern u32 data_021f4474; // 0x021f4474
extern u32 data_021f4478; // 0x021f4478
extern u32 data_021f447c; // 0x021f447c
extern u32 data_021f4488; // 0x021f4488
void func_02064658(void *dst, void *src, u32 size, int flag);
extern unsigned char data_021f445c;
extern unsigned char data_021f4460;
extern unsigned char data_021f4462;
extern unsigned char data_021f4464;
extern unsigned char data_021f4466;

void func_020a99d8(void *arg);
void func_020a98e4(UnkStruct_020a98e4 *self);
int func_020a982c(void *ptr);
int func_020a9754(unsigned char *p);

unsigned int func_020a9ae8(unsigned int *p0)
{
    unsigned char buf[4];
    unsigned char *s;
    unsigned char *d;
    unsigned char *e;
    d = buf;
    s = (unsigned char *) p0 + 4;
    e = (unsigned char *) p0;
    while (s != e) {
        *d++ = *--s;
    }
    return *(unsigned int *) buf;
}

int func_020a9ae4(int *p0)
{
    return p0[0];
}

int func_020a9ae0(unsigned short *p0)
{
    return p0[0];
}

int func_020a9adc(unsigned char *p0)
{
    return p0[0];
}

struct UnkStruct_020a9a90 *func_020a9a90(struct UnkStruct_020a9a90 *self, unsigned char c)
{
    self->unk_00 = &data_020e3d34;
    self->unk_04 = c;
    self->unk_8C = 0;
    self->unk_8D = data_021f43ec;
    self->unk_9C = 0;
    self->unk_A0 = 0;
    FS_InitFile(&self->unk_44);
    MI_CpuFill8(self->unk_05, 0, sizeof(self->unk_05));
    return self;
}

void *func_020a9a78(void *p)
{
    *(void **) p = (void *) &data_020e3d34;
    func_020a99d8(p);
    return p;
}

void *func_020a9a58(void *p)
{
    *(void **) p = ((int *) &data_020e3d34);
    func_020a99d8(p);
    func_020edb3c(p);
    return p;
}

void *func_020a9a40(void *p)
{
    *(void **) p = &data_020e3d34;
    func_020a99d8(p);
    return p;
}

unsigned char func_020a9a08(UnkStruct_020a9a08 *s, const void *src)
{
    unsigned char result;

    strncpy(s->data, src, 0x3E);
    if (FS_OpenFile(s->unk_44, src) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    s->flag = result;
    return s->flag;
}

void func_020a99d8(void *arg)
{
    unsigned char *p;
    unsigned char val;

    p = (unsigned char *) arg;
    if (p[0x8c] != 0) {
        FS_CloseFile((void *) ((unsigned char *) arg + 0x44));
        p[0x8c] = 0;
        val = data_021f43ec;
        p[0x8d] = val;
    }
}

int func_020a9938(UnkStruct_020a9938 *self, const unsigned char *msg)
{
    int flag = 1;

    func_020a98e4((UnkStruct_020a98e4 *) self);
    self->unk_8D = *msg;

    flag = (flag & func_020a982c(self)) != 0;
    if (flag) {
        flag = (flag & func_020a9754((unsigned char *) self)) != 0;
    }
    if (flag) {
        flag = (flag & func_020a9708(self)) != 0;
    }
    if (flag) {
        if (self->unk_04 != 0) {
            flag = (flag & func_020a958c(self)) != 0;
        } else {
            flag = (flag & func_020a967c(self)) != 0;
        }
    }
    if (flag) {
        flag = (flag & func_020a9540(self)) != 0;
    }
    return flag;
}

void func_020a98e4(UnkStruct_020a98e4 *self)
{
    volatile unsigned char scratch[8];

    (void) &scratch;
    self->unk_8D = 0;
    MI_CpuFill8(self->unk_90, 0, 0xc);
    self->unk_9C = 0;
    self->unk_A0 = 0;
    MI_CpuFill8(data_021f446c, 0, 0x20);
    MI_CpuFill8(data_021f4458, 0, 0x14);
    MI_CpuFill8(data_021f4428, 0, 0xc);
}

int func_020a982c(void *ptr)
{
    int ok1, ok2, ok3;

    func_02064658((char *) ptr + 0x44, ((struct UnkStruct_020a982c *) data_021f446c), 0x20, 0);

    (*(struct UnkStruct_020a982c *) data_021f446c).unk_00 = (u32) func_020a9ae8((unsigned int *) (((struct UnkStruct_020a982c *) data_021f446c)));
    (*(struct UnkStruct_020a982c *) data_021f446c).unk_04 = (u32) func_020a9ae8((unsigned int *) (&data_021f4470));
    (*(struct UnkStruct_020a982c *) data_021f446c).unk_08 = (u32) func_020a9ae4((int *) (&data_021f4474));
    (*(struct UnkStruct_020a982c *) data_021f446c).unk_0C = (u32) func_020a9ae4((int *) (&data_021f4478));
    (*(struct UnkStruct_020a982c *) data_021f446c).unk_10 = (u8) func_020a9adc((unsigned char *) (&data_021f447c));
    (*(struct UnkStruct_020a982c *) data_021f446c).unk_1C = (u32) func_020a9ae4((int *) (&data_021f4488));

    ok1 = ((*(struct UnkStruct_020a982c *) data_021f446c).unk_04 == 0x626d6731);
    ok2 = ((*(struct UnkStruct_020a982c *) data_021f446c).unk_08 != 0);
    ok3 = ((*(struct UnkStruct_020a982c *) data_021f446c).unk_0C == 2);

    if ((*(struct UnkStruct_020a982c *) data_021f446c).unk_00 == 0x4d455347 && ok1 && ok2 && ok3) {
        return 1;
    }
    return 0;
}

int func_020a9754(unsigned char *p)
{
    int cond1, cond2, cond3, cond4;
    unsigned short fs;

    func_02064658(p + 0x44, (void *) ((const void *) ((struct GStruct *) data_021f4458)), 0x14, 0x20);

    (*(struct GStruct *) data_021f4458).unk_00 = (int) func_020a9ae8((unsigned int *) ((void *) ((struct GStruct *) data_021f4458)));
    (*(struct GStruct *) data_021f4458).unk_04 = func_020a9ae4((int *) ((void *) &data_021f445c));
    (*(struct GStruct *) data_021f4458).unk_08 = func_020a9ae0((unsigned short *) ((void *) &data_021f4460));
    (*(struct GStruct *) data_021f4458).unk_0A = func_020a9ae0((unsigned short *) ((void *) &data_021f4462));
    (*(struct GStruct *) data_021f4458).unk_0C = func_020a9ae0((unsigned short *) ((void *) &data_021f4464));
    (*(struct GStruct *) data_021f4458).unk_0E = func_020a9adc((unsigned char *) ((void *) &data_021f4466));

    cond1 = ((*(struct GStruct *) data_021f4458).unk_00 == 0x494e4631);
    fs = (*(struct GStruct *) data_021f4458).unk_08;
    cond2 = 0;
    if (fs <= 0x100) {
        if (p[0x8d] < fs) {
            cond2 = 1;
        }
    }
    cond3 = ((*(struct GStruct *) data_021f4458).unk_0A == (p[4] != 0 ? 0xc : 4));
    cond4 = ((*(struct GStruct *) data_021f4458).unk_0C == 0);

    if (cond1 && cond2 && cond3 && cond4) {
        return 1;
    }
    return 0;
}
