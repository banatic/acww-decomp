/* catalog_handle: 7 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229d52c @ 0x0229d52c, 0x20 bytes, Thumb
 * func_ov114_0229d500 @ 0x0229d500, 0x2c bytes, Thumb
 * func_ov114_0229d4c0 @ 0x0229d4c0, 0x40 bytes, Thumb
 * func_ov114_0229d3f4 @ 0x0229d3f4, 0xcc bytes, Thumb
 * func_ov114_0229d32c @ 0x0229d32c, 0xc8 bytes, Thumb
 * func_ov114_0229d304 @ 0x0229d304, 0x28 bytes, Thumb
 * func_ov114_0229d2d8 @ 0x0229d2d8, 0x2c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229d500 {
    char pad_00[0x1270];
    int unk_1270;
    char pad_1274[8];
    int unk_127C;
    char pad_1280[24];
    int unk_1298;
};

typedef struct {
    char pad_00[0x1270];
    int a; // 0x1270
    char pad_1274[0x1280 - 0x1274];
    int c; // 0x1280
    char pad_1284[0x1298 - 0x1284];
    int b; // 0x1298
} UnkStruct_0229d4c0;

typedef struct {
    u8 pad_00[0x121c];
    u8 sub_121c[0x54];
    int unk_1270;
    int unk_1274;
    int unk_1278;
    u8 pad_127C[0x3f];
    u8 unk_12BB;
} UnkStruct_0229d3f4;

struct UnkStruct_0229d32c {
    unsigned char pad_00[0x121c];
    unsigned char unk_121C;
    unsigned char pad_121D[0x53];
    int unk_1270;
    int unk_1274;
    int unk_1278;
    unsigned char pad_127C[0x3f];
    unsigned char unk_12BB;
};

typedef struct {
    char pad_00[0x121c];
    char unk_121C;
    char pad_121D[158];
    unsigned char flag;
} UnkStruct_0229d304;

struct UnkStruct_0229d2d8 {
    unsigned char pad_00[0x121c];
    unsigned char sub[0x9f];
    unsigned char flag;
};

extern void func_0208ea70(int *object, int a, int b);
extern int _s32_div_f(int, int);
extern int func_ov114_0229cb7c(UnkStruct_0229d4c0 *self, int arg);
extern void func_ov114_0229cadc(UnkStruct_0229d4c0 *self);
extern int func_ov002_0220a58c(void *, int arg1, int arg2);
extern void func_ov002_0220a574(void *);
extern int func_02088d34(const void *, int, int, int, int);
extern const u8 data_ov114_0229db00[];
extern const u8 data_ov114_0229db08[];
extern void func_ov002_0220a4c8(void *receiver);
extern int func_020e895c(int *ptr, int value, int arg2);
extern int func_ov002_0220a568(void *);
extern int func_0208e930(const void *ptr);
extern void func_ov114_0229d244(void *self);

void func_ov114_0229d52c(void *self, int param)
{
    int *field = (int *) ((char *) self + 0x121c);
    func_0208ea70(field, (int) (*(unsigned int *) ((char *) self + 0x1270) - 0x4eU), (int) ((unsigned int) param + 0x4aU));
}

void func_ov114_0229d500(struct UnkStruct_0229d500 *p)
{
    p->unk_1270 = _s32_div_f(p->unk_127C * 0x8c, p->unk_1298);
}

void func_ov114_0229d4c0(UnkStruct_0229d4c0 *self)
{
    int quotient;
    quotient = (self->a * self->b) / 0x8c;
    if (func_ov114_0229cb7c(self, quotient) != 0) {
        func_ov114_0229cadc(self);
    }
    self->c = 0;
}

int func_ov114_0229d3f4(UnkStruct_0229d3f4 *self, int x, int y)
{
    int dx;
    unsigned int dy;

    if (func_ov002_0220a58c(self->sub_121c, x, y)) {
        self->unk_1274 = self->unk_1270 - x;
        func_ov002_0220a574(self->sub_121c);
        self->unk_12BB = 2;
        self->unk_1278 = self->unk_1270;
        return 1;
    }
    dx = x - 0x80;
    dy = y;
    dy -= 0x60;
    if (func_02088d34(data_ov114_0229db00, dx, dy, 2, 2)) {
        self->unk_12BB = 0;
        return 1;
    }
    if (func_02088d34(data_ov114_0229db08, dx, dy, 2, 2)) {
        self->unk_12BB = 1;
        return 1;
    }
    if (x > 0x3a && x < 0xc6 && y > 0xac && y < 0xb8) {
        func_ov002_0220a574(self->sub_121c);
        self->unk_12BB = 3;
        self->unk_1278 = self->unk_1270;
        return 1;
    }
    return 0;
}

void func_ov114_0229d32c(struct UnkStruct_0229d32c *self, int param)
{
    int old = self->unk_1270;
    int diff;

    switch (self->unk_12BB) {
        case 2:
            param += self->unk_1274;
            self->unk_1270 = param;
            break;
        case 0:
            param = old - 2;
            self->unk_1270 = param;
            break;
        case 1:
            param = old + 2;
            self->unk_1270 = param;
            break;
        case 3:
            param -= 0x3a;
            func_020e895c(&self->unk_1270, param, 4);
            break;
    }

    if (self->unk_1270 < 0) {
        self->unk_1270 = 0;
    }
    if (self->unk_1270 > 0x8c) {
        self->unk_1270 = 0x8c;
    }

    func_ov114_0229d4c0((UnkStruct_0229d4c0 *) self);

    if (self->unk_12BB == 2) {
        diff = self->unk_1278 - self->unk_1270;
        if (diff >= 4 || diff <= -4) {
            func_ov002_0220a4c8(&self->unk_121C);
            self->unk_1278 = self->unk_1270;
        }
    } else {
        if (self->unk_1270 != old) {
            func_ov002_0220a4c8(&self->unk_121C);
        }
    }
}

void func_ov114_0229d304(UnkStruct_0229d304 *p)
{
    if (p->flag == 2) {
        func_ov002_0220a568(&p->unk_121C);
    }
    p->flag = 4;
}

int func_ov114_0229d2d8(struct UnkStruct_0229d2d8 *self)
{
    if (self->flag == 2) {
        return func_0208e930(self->sub);
    } else {
        func_ov114_0229d244(self);
        return 1;
    }
}
