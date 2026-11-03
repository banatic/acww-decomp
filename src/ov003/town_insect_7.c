/* town_insect_7: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02230168 @ 0x02230168, 0x18 bytes, Thumb
 * func_ov003_02230120 @ 0x02230120, 0x48 bytes, Thumb
 * func_ov003_022300e0 @ 0x022300e0, 0x40 bytes, Thumb
 * func_ov003_02230098 @ 0x02230098, 0x48 bytes, Thumb
 * func_ov003_0222ffdc @ 0x0222ffdc, 0xbc bytes, Thumb
 * func_ov003_0222ff74 @ 0x0222ff74, 0x68 bytes, Thumb
 * func_ov003_0222ff2c @ 0x0222ff2c, 0x48 bytes, Thumb
 * func_ov003_0222fe18 @ 0x0222fe18, 0x114 bytes, Thumb
 * func_ov003_0222fd60 @ 0x0222fd60, 0xb8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    char pad_20[0x130 - 0x20];
    char sub130[0x100];
    char sub230[0x19];
    unsigned char unk_249;
    char pad_24A[3];
    unsigned char unk_24D;
    char pad_24E[2];
    unsigned char unk_250;
    char pad_251[0xb];
} UnkStruct_0222ff74;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222fd60;

extern void *func_020edf70(int size);
extern void *data_ov003_0223c0fc[];
extern void *data_020da13c[];
extern void *func_020ee660(void *a);
extern void func_ov003_02235d5c(void *a);
extern void func_0209d2b8(void *a);
extern unsigned char data_ov003_02260540;
extern void func_0209d2b4(void *a);
extern void func_ov003_02235d58(void *a);
extern void func_020ee62c(void *a);
extern void func_020edf54(void *a);
extern void *func_0209d238(void *a, void *b);
extern void func_0209d0a4(void *a);
extern UnkStruct_0222ff74 data_ov003_02260994[];
extern void func_02042200(void);
extern void func_02054fcc(void *p);
extern void func_02004280(void *p);
extern void func_0209d090(void *p);
extern void func_0209d200(void *a, void *b);
extern UnkStruct_0222fd60 *data_020ccf94;
extern int func_0205c9c8(int size, int heapword);
extern void func_0205c9ac(void);
extern int func_0205ca30(int size, int heapword);
extern void func_0205ca14(void);
extern int func_0205c9fc(int size, int heapword);
extern void func_0205c9e0(void);
extern int func_0209d180(void *self, unsigned int count, int a, int b, int size, int (*allocate)(int, int),
                         void (*cleanup)(void), void *context);
extern int func_02073dd4(void *a, int b);
extern void func_ov003_0222c758(void);

void *func_ov003_02230120(char *self);
void func_ov003_0222fe18(char *a0, char *self, int mode);

void func_ov003_02230168(void)
{
    void *condition_value_18;
    condition_value_18 = (void *) (func_020edf70(0xa0));
    if (condition_value_18 != 0) {
        func_ov003_02230120((char *) condition_value_18);
    }
}

void *func_ov003_02230120(char *self)
{
    func_020ee660(self);
    *(void **) self = data_020da13c;
    func_ov003_02235d5c(self);
    *(void **) self = data_ov003_0223c0fc;
    func_0209d2b8(self + 0x50);
    func_0209d2b8(self + 0x68);
    func_0209d2b8(self + 0x80);
    data_ov003_02260540 = 0;
    return self;
}

void *func_ov003_022300e0(char *self)
{
    *(void **) self = data_ov003_0223c0fc;
    func_0209d2b4(self + 0x80);
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    func_ov003_02235d58(self);
    *(void **) self = data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov003_02230098(char *self)
{
    *(void **) self = data_ov003_0223c0fc;
    func_0209d2b4(self + 0x80);
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    func_ov003_02235d58(self);
    *(void **) self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_0222ffdc(char *a0, char *self)
{
    signed char k;
    u8 s;
    int t[3];
    int u[3];
    short w;
    int *p;

    if (*(u8 *) (self + 0x250) != 0) {
        k = *(signed char *) (self + 0x24d);
        s = *(u8 *) (self + 0x251);
        p = (int *) (self + 0x204);
        t[0] = p[0];
        t[1] = p[1];
        t[2] = p[2];
        p = (int *) (self + 0x1d4);
        u[0] = p[0];
        u[1] = p[1];
        u[2] = p[2];
        w = *(short *) (self + 0x23a);
        func_ov003_0222fe18((char *) a0, (char *) self, 3);
        *(signed char *) (self + 0x24d) = k;
        *(u8 *) (self + 0x251) = s;
        p = (int *) (self + 0x204);
        p[0] = t[0];
        p[1] = t[1];
        p[2] = t[2];
        *(short *) (self + 0x23a) = w;
        p = (int *) (self + 0x1d4);
        p[0] = u[0];
        p[1] = u[1];
        p[2] = u[2];
    }
    *(u8 *) (self + 0x250) = 2;
    a0 = a0 + 0x80;
    func_0209d238(a0, self + 0x230);
    func_0209d0a4(self + 0x130);
    *(u8 *) (self + 0x249) = 1;
    return 1;
}

int func_ov003_0222ff74(char *a, int e, int idx)
{
    UnkStruct_0222ff74 *s = &data_ov003_02260994[idx];
    if (s->unk_250 == 0) {
        func_0209d238((void *) (a + 0x68), (void *) s->sub230);
        func_0209d0a4((void *) s->sub130);
        s->unk_249 = 1;
        s->unk_18 = 0;
        s->unk_1C = 0;
        s->unk_24D = (unsigned char) e;
        s->unk_250 = 2;
        return 1;
    }
    return 0;
}

int func_ov003_0222ff2c(char *a, unsigned char *o)
{
    if (o[0x250] == 0) {
        o[0x250] = 2;
        func_0209d238((void *) (a + 0x50), (void *) (o + 0x230));
        func_0209d0a4((void *) (o + 0x130));
        o[0x249] = 0;
        return 1;
    }
    return 0;
}

void func_ov003_0222fe18(char *a0, char *self, int mode)
{
    int *p;
    int *q;

    p = (int *) (self + 0x204);
    q = (int *) (self + 0x1d4);
    if (*(s8 *) (self + 0x24d) == 0x33) {
        func_02042200();
    }
    if (*(s8 *) (self + 0x24d) >= 0) {
        func_02054fcc(self + 0x50);
    }
    *(u8 *) (self + 0x250) = 0;
    *(int *) (self + 0x21c) = 0;
    func_02004280(self + 0x174);
    p[0] = 1;
    p[1] = 1;
    p[2] = 1;
    q[0] = 1;
    q[1] = 1;
    q[2] = 1;
    *(u8 *) (self + 0x248) = 0;
    *(u8 *) (self + 0x249) = 0;
    *(u8 *) (self + 0x258) = 0;
    *(s8 *) (self + 0x24d) = -1;
    *(short *) (self + 0x23a) = 0;
    *(short *) (self + 0x242) = 0;
    *(u8 *) (self + 0x251) = 0x13;
    func_0209d090(self + 0x130);
    *(int *) (self + 0x18) = 0;
    *(int *) (self + 0x1c) = 0;
    *(u8 *) (self + 0x254) = 0;
    *(u8 *) (self + 0x24a) = 0;
    *(short *) (self + 0x236) = 0;
    if (mode == 1) {
        func_0209d200(a0 + 0x50, self + 0x230);
    } else if (mode == 2) {
        func_0209d200(a0 + 0x68, self + 0x230);
    } else {
        func_0209d200(a0 + 0x80, self + 0x230);
    }
    *(int *) (self + 0x170) = 0;
}

int func_ov003_0222fd60(char *self)
{
    UnkStruct_0222fd60 *context;
    func_0209d180(self + 0x50, 8, 0x400, 0x40, 0x9c4, func_0205c9c8, func_0205c9ac, 0);
    func_0209d180(self + 0x68, 2, 0x400, 0x40, 0x6e8, func_0205ca30, func_0205ca14, 0);
    func_0209d180(self + 0x80, 4, 0x400, 0x40, 0x9c4, func_0205c9fc, func_0205c9e0, 0);
    context = data_020ccf94;
    if (func_02073dd4(context, context->unk_64) == 0) {
        func_ov003_0222ff74((char *) self, 0x3a, 0);
        func_ov003_0222ff74((char *) self, 0x3b, 1);
    }
    func_ov003_0222c758();
    return 1;
}
