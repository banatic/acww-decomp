/* field_actor_26: 21 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02212830 @ 0x02212830, 0x48 bytes, Thumb
 * func_ov003_02212824 @ 0x02212824, 0xa bytes, Thumb
 * func_ov003_02212818 @ 0x02212818, 0xa bytes, Thumb
 * func_ov003_0221280c @ 0x0221280c, 0xa bytes, Thumb
 * func_ov003_022127a0 @ 0x022127a0, 0x6c bytes, Thumb
 * func_ov003_02212768 @ 0x02212768, 0x38 bytes, Thumb
 * func_ov003_02212728 @ 0x02212728, 0x40 bytes, Thumb
 * func_ov003_02212574 @ 0x02212574, 0x1b4 bytes, Thumb
 * func_ov003_022124c4 @ 0x022124c4, 0xb0 bytes, Thumb
 * func_ov003_0221248c @ 0x0221248c, 0x36 bytes, Thumb
 * func_ov003_02212478 @ 0x02212478, 0x14 bytes, Thumb
 * func_ov003_0221246c @ 0x0221246c, 0xc bytes, Thumb
 * func_ov003_0221243c @ 0x0221243c, 0x30 bytes, Thumb
 * func_ov003_022123fc @ 0x022123fc, 0x40 bytes, Thumb
 * func_ov003_022123e0 @ 0x022123e0, 0x1a bytes, Thumb
 * func_ov003_022123a8 @ 0x022123a8, 0x36 bytes, Thumb
 * func_ov003_02212394 @ 0x02212394, 0x14 bytes, Thumb
 * func_ov003_02212388 @ 0x02212388, 0xc bytes, Thumb
 * func_ov003_02212348 @ 0x02212348, 0x40 bytes, Thumb
 * func_ov003_02212308 @ 0x02212308, 0x40 bytes, Thumb
 * func_ov003_022122fc @ 0x022122fc, 0xc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02212824 {
    int a;
    int b;
};

struct UnkStruct_02212818 {
    int a;
    int b;
};

struct UnkStruct_0221280c {
    int a;
    int b;
};

struct UnkStruct_02212728 {
    char pad_00[0x1c4];
    unsigned char unk_1C4;
    char pad_1C5[0x60f];
    unsigned char arr[2];
};

typedef struct {
    char pad_00[0x98];
    void *unk_98;
    char pad_9C[0x7d4 - 0x9c];
    unsigned char data[3];
    char pad_7D7[0x80c - 0x7d7];
    int unk_80C;
} UnkStruct_02212574;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022124c4 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    char unk_8E[0x98 - 0x8e];
    void *unk_98;
    char pad_9C[0x7f0 - 0x9c];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    unsigned int unk_7FC;
    unsigned int unk_800;
} UnkStruct_022124c4;

struct UnkStruct_02212348 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x51c];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

struct UnkStruct_02212308 {
    char pad_00[0x98];
    void *unk_98;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02212878(void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109fc(void *, int, int, int);
extern void func_0204f794(char *buf, unsigned char a, unsigned char b);
extern void func_02010d88(void *p, char *buf, int c, int d);
extern void func_02089fc8(void *p);
extern void func_0204f818(int *a, int *b, Vec3 *in);
extern int func_ov003_0220cf68(UnkStruct_02212574 *self, Vec3 *in, unsigned char *flag);
extern int func_ov003_022122ac(UnkStruct_02212574 *self, int a, int *vec, int b, int c);
extern int func_ov003_02211d4c(UnkStruct_02212574 *self, int a, int *vec, int b, int c);
extern int func_ov003_02211980(UnkStruct_02212574 *self, int *vec, int a, int b, int c);
extern void *func_ov003_022109f8(UnkStruct_02212574 *self, int a, int *vec, int b, int c, int d);
extern int func_02011398(void *, int);
extern void func_0201107c(void *, int *);
extern void func_02010f5c(void *);
extern int func_02073908(int, unsigned int);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_0200f554(void *);
extern int func_020912d4(int, void *, void *, int);
extern int data_020ccf94;
extern void func_020109a0(int a, int b, int c, unsigned short d);
extern int func_02056f28(char *p, int a);
extern int func_0200f328(char *p, int b);
extern int func_02056f94(void *p);
extern int func_02008258(void *p, int value);
extern int func_0200d4e8(void *p, int a, int b, int c);
extern void *func_020113a4(void *, int, int);

int func_ov003_0221248c(int a, int b, int c);
int func_ov003_022123a8(void *a, int b, int c);

void *func_ov003_02212830(void *arg0, int *arg1, int arg2, int arg3)
{
    int buf1[2];
    unsigned char buf2[12];
    unsigned char buf3[16];
    void *result;

    func_0200e92c(buf2);
    func_0200e90c(buf2, 0x5a, arg2, arg3);
    buf1[0] = arg1[0];
    buf1[1] = arg1[1];
    func_ov003_02212878(buf3, buf1);
    result = func_0200e894(arg0, buf2);
    func_0200e91c(buf2);
    return result;
}

void func_ov003_02212824(u8 *d, struct UnkStruct_02212824 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}

void func_ov003_02212818(u8 *d, struct UnkStruct_02212818 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}

void func_ov003_0221280c(u8 *p, struct UnkStruct_0221280c *d)
{
    d->a = p[0];
    d->b = p[1];
}

void func_ov003_022127a0(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    int b1 = p[1];
    unsigned char *d = (unsigned char *) self + 0x7d4;
    int b0 = p[0];
    int loc[2], loc2[2];

    loc[0] = b0;
    loc[1] = b1;
    func_ov003_02212824((u8 *) d, (struct UnkStruct_02212824 *) loc);
    if (*(int *) ((char *) self + 0x80c) == -1) {
        d[2] = 0;
    } else {
        d[2] = 1;
    }
    loc2[0] = b0;
    loc2[1] = b1;
    func_ov003_02212818((u8 *) ((char *) self + 0x8f0), (struct UnkStruct_02212818 *) loc2);
    if (*(int *) ((char *) self + 0x704) == 0x4a) {
        func_020109fc(self, 0x4a, 3, 0);
    }
}

void func_ov003_02212768(char *a, void *b)
{
    int p[2];
    int q[2];

    p[0] = 0;
    p[1] = 0;
    func_ov003_0221280c((u8 *) (a + 0x8f0), (struct UnkStruct_0221280c *) p);
    q[0] = p[0];
    q[1] = p[1];
    func_ov003_02212830(a, (int *) q, 6, (int) b);
}

void func_ov003_02212728(struct UnkStruct_02212728 *p)
{
    char buf[16];
    unsigned char *bp = &p->arr[0];
    func_0204f794(buf, *bp, *(bp + 1));
    func_02010d88(p, buf, 0xf33, 0x1000);
    func_02089fc8(&p->unk_1C4);
}

int func_ov003_02212574(UnkStruct_02212574 *self, Vec3 *src, unsigned char flag)
{
    int r6;
    int r7;
    unsigned char *r5;
    Vec3 buffer;
    int a, b;
    int c, d;
    int local2[2];
    int local6[2];
    int local7[2];
    Vec3 local3, local4, local5, local8;

    if (self->unk_98) {
        return -1;
    }

    r7 = 0;
    r5 = (unsigned char *) self + 0x7d4;

    if (flag) {
        buffer.x = src->x;
        buffer.y = src->y;
        buffer.z = src->z;
    } else {
        func_0204f794((char *) (&buffer), r5[0], r5[1]);
        if (r5[2] == 0) {
            r7 = 1;
            flag = 1;
        }
    }

    r6 = func_ov003_0220cf68(self, &buffer, &flag);

    a = 0;
    b = 0;
    func_0204f818(&a, &b, &buffer);

    if (r7 != 0) {
        if (self->unk_80C != -1) {
            r5[2] = 1;
        }
    }

    switch (r6) {
        case 0:
            break;
        case 1:
            func_ov003_0221248c((int) self, 6, -1);
            break;
        case 2:
            local2[0] = a;
            local2[1] = b;
            func_ov003_022122ac(self, 0, local2, 6, -1);
            break;
        case 3:
            local3.x = buffer.x;
            local3.y = buffer.y;
            local3.z = buffer.z;
            func_ov003_02211d4c(self, 0, (int *) &local3, 6, -1);
            break;
        case 4:
            local4.x = buffer.x;
            local4.y = buffer.y;
            local4.z = buffer.z;
            func_ov003_02211d4c(self, 1, (int *) &local4, 6, -1);
            break;
        case 5:
            local5.x = buffer.x;
            local5.y = buffer.y;
            local5.z = buffer.z;
            func_ov003_02211980(self, (int *) &local5, 0, 6, -1);
            break;
        case 6:
            c = 0;
            d = 0;
            func_0204f818(&c, &d, &buffer);
            local6[0] = c;
            local6[1] = d;
            func_ov003_022109f8(self, 0, local6, 0xfff1, 6, -1);
            break;
        case 7:
            func_ov003_022123a8((void *) self, 6, -1);
            break;
        case 8:
            local7[0] = a;
            local7[1] = b;
            func_ov003_022122ac(self, 1, local7, 6, -1);
            break;
        case 9:
            local8.x = buffer.x;
            local8.y = buffer.y;
            local8.z = buffer.z;
            func_ov003_02211980(self, (int *) &local8, 1, 6, -1);
            break;
    }

    return r6;
}

void func_ov003_022124c4(UnkStruct_022124c4 *self)
{
    void *obj;
    int tmp0;
    int arr[3];

    obj = self->unk_98;
    tmp0 = func_02011398(obj, 0);
    func_0201107c(self, &tmp0);
    func_02010f5c(self);

    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_0201100c(self);
        func_02010d64(self);
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        func_ov003_02212574((UnkStruct_02212574 *) self, (Vec3 *) arr, 0);
    } else {
        if (func_0200f554(self)) {
            func_0201100c(self);
        }
        func_02010d64(self);
        self->unk_7FC = (unsigned int) func_02008258(self, self->unk_7F0);
    }

    func_ov003_02212728((struct UnkStruct_02212728 *) self);

    if (obj != 0 && self->unk_98 == 0) {
        func_020912d4(0x2a, (void *) ((char *) self + 0x5c), (void *) ((char *) self + 0x8e), 0);
    }
}

int func_ov003_0221248c(int a, int b, int c)
{
    char buf[0x20];
    int ret;
    func_0200e92c((void *) buf);
    func_0200e90c((void *) buf, 0x5B, b, c);
    ret = (int) func_0200e894((void *) a, (void *) buf);
    func_0200e91c((void *) buf);
    return ret;
}

void func_ov003_02212478(int a, void *message, int previous)
{
    func_020109a0(a, 0x4d, 3, 0);
}

void func_ov003_0221246c(int a, int b)
{
    func_ov003_0221248c(a, 6, b);
}

void func_ov003_0221243c(char *p)
{
    if (func_02056f28(p + 0x2d0, 5)) {
        func_0200f328(p, 0x842);
    }
    func_02010f5c((void *) p);
}

void func_ov003_022123fc(char *p)
{
    if (func_02056f94(p + 0x2d0)) {
        *(int *) (p + 0x7fc) = func_02008258(p, *(int *) (p + 0x7f0));
        func_0200d4e8(p, 3, 1, -1);
    }
}

void func_ov003_022123e0(void *p)
{
    func_ov003_0221243c((char *) p);
    func_02010d64(p);
    func_ov003_022123fc((char *) p);
}

int func_ov003_022123a8(void *a, int b, int c)
{
    char buf[0x20];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x5c, b, c);
    result = (int) func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}

void func_ov003_02212394(int a, void *message, int previous)
{
    func_020109a0(a, 0x5e, 3, 0);
}

void func_ov003_02212388(int a, int b)
{
    func_ov003_022123a8((void *) a, 6, b);
}

void func_ov003_02212348(struct UnkStruct_02212348 *self)
{
    if (func_02056f94(&self->unk_2D0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
}

void func_ov003_02212308(struct UnkStruct_02212308 *self)
{
    void *v;

    func_02010f5c(self);
    func_0201100c(self);
    func_02010d64(self);
    v = func_020113a4(self->unk_98, 0, 0x171);
    func_0201107c(self, (int *) (&v));
    func_ov003_02212348((struct UnkStruct_02212348 *) self);
}

void func_ov003_022122fc(unsigned char *r0, unsigned int *r1, unsigned char r2)
{
    r0[0] = (unsigned char) r1[0];
    r0[1] = (unsigned char) r1[1];
    r0[2] = r2;
}
