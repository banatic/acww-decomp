/* catalog_pages: 13 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229d220 @ 0x0229d220, 0x24 bytes, Thumb
 * func_ov114_0229d1dc @ 0x0229d1dc, 0x44 bytes, Thumb
 * func_ov114_0229d168 @ 0x0229d168, 0x74 bytes, Thumb
 * func_ov114_0229d148 @ 0x0229d148, 0x20 bytes, Thumb
 * func_ov114_0229d130 @ 0x0229d130, 0x18 bytes, Thumb
 * func_ov114_0229d110 @ 0x0229d110, 0x20 bytes, Thumb
 * func_ov114_0229d108 @ 0x0229d108, 0x8 bytes, Thumb
 * func_ov114_0229d104 @ 0x0229d104, 0x4 bytes, Thumb
 * func_ov114_0229d088 @ 0x0229d088, 0x7c bytes, Thumb
 * func_ov114_0229d030 @ 0x0229d030, 0x58 bytes, Thumb
 * func_ov114_0229cf58 @ 0x0229cf58, 0xd8 bytes, Thumb
 * func_ov114_0229cf18 @ 0x0229cf18, 0x40 bytes, Thumb
 * func_ov114_0229cee0 @ 0x0229cee0, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[0x9f];
} UnkStruct_0229d1dc_2;

typedef struct {
    char pad_00[0x121c];
    UnkStruct_0229d1dc_2 sub;
    unsigned char flag;
} UnkStruct_0229d1dc;

typedef struct UnkStruct_0229d168 {
    char pad_00[0x127c];
    int unk_127C;
    int unk_1280;
} UnkStruct_0229d168;

typedef struct {
    char pad_00[0x808];
    char buffer[0xAA8];
    unsigned char flag_12b0;
    char pad_12B1[0x4];
    unsigned char flag_12b5;
    char pad_12B6[0x1];
    unsigned char mode_12b7;
    unsigned char flag_12b8;
} UnkStruct_0229d088;

typedef struct {
    char pad_00[0x81a];
    char unk_81A;
    char pad_81B[0x129c - 0x81b];
    int unk_129C;
    int unk_12A0;
    char pad_12A4[0x12b0 - 0x12a4];
    u8 unk_12B0;
    u8 unk_12B1;
    char pad_12B2[3];
    u8 unk_12B5;
} UnkStruct_0229cf58;

typedef struct {
    char pad_00[0x12ae];
    unsigned char unk_12AE;
    char pad_12AF[1];
    unsigned char unk_12B0;
    char pad_12B1[4];
    unsigned char unk_12B5;
} UnkStruct_0229cf18;

extern int func_ov002_0220a568(void *);
extern int func_0208e930(UnkStruct_0229d1dc_2 *);
extern void func_ov002_0220a580(UnkStruct_0229d1dc_2 *);
extern void func_ov114_0229d500(UnkStruct_0229d168 *p);
extern int func_ov114_0229cb7c(UnkStruct_0229d168 *p, int value);
extern void func_ov114_0229cadc(UnkStruct_0229d168 *p);
extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_ov114_0229daf0[];
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *obj);
extern const char data_ov114_0229dbac[];
extern const char data_ov114_0229dbbc[];
extern int func_020b4a20(void *buf, unsigned char *byte, const char *data);
extern int func_020a7bf4(u8 *p, int n);
extern void *func_ov114_0229cd70(UnkStruct_0229cf58 *self);
extern int func_020a8a34(void *h, int a);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);
extern void func_0200467c(int cmd);

int func_ov114_0229d030(u8 *base);
void func_ov114_0229cf58(UnkStruct_0229cf58 *self);

void func_ov114_0229d220(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x12bb) == 2) {
        func_ov002_0220a568((char *) self + 0x121c);
    }
}

int func_ov114_0229d1dc(UnkStruct_0229d1dc *self)
{
    if (self->flag == 2) {
        if (func_0208e930(&self->sub)) {
            func_ov002_0220a580(&self->sub);
            self->flag = 4;
            return 1;
        }
    } else {
        self->flag = 4;
        return 1;
    }
    return 0;
}

void func_ov114_0229d168(UnkStruct_0229d168 *p)
{
    int acc = p->unk_127C;
    int val = p->unk_1280;

    if (val > 0) {
        if (val < 0xb) {
            acc += val;
            p->unk_1280 = 0;
        } else {
            acc += 0xb;
            p->unk_1280 = val - 0xb;
        }
    } else if (val < 0) {
        if (val > -11) {
            acc += val;
            p->unk_1280 = 0;
        } else {
            acc -= 0xb;
            p->unk_1280 = val + 0xb;
        }
    }

    if (acc != p->unk_127C) {
        func_ov114_0229d500(p);
        if (func_ov114_0229cb7c(p, acc) != 0) {
            func_ov114_0229cadc(p);
        }
    }
}

void *func_ov114_0229d148(void *self)
{
    func_020a8cac(self);
    *(void **) self = ((char *) data_ov114_0229daf0);
    func_020a8c1c(self);
    return self;
}

void *func_ov114_0229d130(void *arg)
{
    *(void **) arg = data_ov114_0229daf0;
    func_020a8c38(arg);
    return arg;
}

void *func_ov114_0229d110(void *obj)
{
    *(void **) obj = ((char *) data_ov114_0229daf0);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov114_0229d108(void)
{
    return 266;
}

int func_ov114_0229d104(int p0)
{
    return ((int) (p0) + (18));
}

void func_ov114_0229d088(UnkStruct_0229d088 *obj)
{
    unsigned char flag;
    unsigned char mode;
    unsigned char local;
    const char *ptr;

    flag = obj->flag_12b8;
    mode = obj->mode_12b7;

    switch (mode) {
        case 0:
            ptr = data_ov114_0229dbac;
            break;
        case 1:
            ptr = data_ov114_0229dbbc;
            break;
        default:
            break;
    }

    if (flag == 0xff) {
        func_020a8c1c(obj->buffer);
        obj->flag_12b0 = 1;
    } else {
        local = flag;
        func_020b4a20(obj->buffer, &local, ptr);
        obj->flag_12b0 = (unsigned char) func_ov114_0229d030((u8 *) obj);
    }

    obj->flag_12b5 = 0;
    func_ov114_0229cf58((UnkStruct_0229cf58 *) obj);
}

int func_ov114_0229d030(u8 *base)
{
    int i = 0;
    int j = i;
    while (i < 4) {
        int a = func_020a7bf4(base + 0x81a, j);
        int b = func_020a7bf4(base + 0x81a, j + 1);
        int c = func_020a7bf4(base + 0x81a, j + 2);
        j += 3;
        if (a == 0 && b == 0 && c == 0) {
            return (u8) i;
        }
        i++;
    }
    return 4;
}

void func_ov114_0229cf58(UnkStruct_0229cf58 *self)
{
    void *h[3];
    void *cur;
    int i;
    int idx;
    int y;
    int r;

    idx = self->unk_12B5 * 3;
    h[0] = func_ov114_0229cd70(self);
    h[1] = func_ov114_0229cd70(self);
    h[2] = func_ov114_0229cd70(self);
    y = 0xbb;
    for (i = 0; i < 3; i++) {
        r = func_020a7bf4((u8 *) (&self->unk_81A), idx);
        if (r != 0) {
            cur = h[i];
            func_020a8a34(cur, r);
        } else {
            cur = h[i];
            func_020a8c1c(cur);
        }
        func_02070adc(cur, self->unk_12B1, y, 0xd, 2, 3, 0);
        func_02070a04(cur, 0, 0);
        idx++;
        y += 0x1a;
    }
    if (self->unk_12B5 == 0) {
        self->unk_12A0 = 4;
    } else {
        self->unk_12A0 = 5;
    }
    if (self->unk_12B5 + 1 >= self->unk_12B0) {
        self->unk_129C = 4;
    } else {
        self->unk_129C = 5;
    }
}

int func_ov114_0229cf18(UnkStruct_0229cf18 *p)
{
    if (p->unk_12B5 + 1 < p->unk_12B0) {
        p->unk_12B5 = p->unk_12B5 + 1;
        p->unk_12AE = 5;
        func_ov114_0229cf58((UnkStruct_0229cf58 *) ((void *) p));
        func_0200467c(0x39);
        return 1;
    }
    return 0;
}

int func_ov114_0229cee0(unsigned char *p)
{
    if (p[0x12b5] != 0) {
        p[0x12b5]--;
        p[0x12af] = 5;
        func_ov114_0229cf58((UnkStruct_0229cf58 *) p);
        func_0200467c(0x39);
        return 1;
    } else {
        return 0;
    }
}
