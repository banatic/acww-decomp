/* model_loader: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02055b00 @ 0x02055b00, 0x34 bytes, Thumb
 * func_02055af4 @ 0x02055af4, 0xc bytes, Thumb
 * func_02055adc @ 0x02055adc, 0x18 bytes, Thumb
 * func_02055aac @ 0x02055aac, 0x2e bytes, Thumb
 * func_020559d0 @ 0x020559d0, 0xdc bytes, Thumb
 * func_02055954 @ 0x02055954, 0x7c bytes, Thumb
 * func_02055950 @ 0x02055950, 0x4 bytes, Thumb
 * func_0205594c @ 0x0205594c, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char *data;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char sub[0x1C];
    char unk_30;
    char unk_31;
} UnkStruct_02055b00;

typedef struct {
    void *vtable;
} Object;

typedef struct {
    u8 pad_00[4];
    void *unk_04;
    void *unk_08;
    void *unk_0C;
    u8 pad_10[4];
    u8 unk_14[13];
    u8 unk_21;
    u8 pad_22[14];
    u8 unk_30;
} UnkStruct_020559d0;

typedef struct {
    u8 pad_00[0x10];
    u32 unk_10;
    u8 unk_14[0x0D];
    u8 unk_21;
    u8 pad_22[0x0E];
    u8 unk_30;
} UnkStruct_02055954;

extern char data_020dd10c[];
extern void *func_020ba01c(void *);
extern void func_020edb3c(void *obj);
extern void func_020b9ec4(void *p);
extern void func_020e993c(void *p, int q);
extern void *data_021fbe94;
extern void *func_02064b2c(int a, void *b, int c, int d);
extern void func_02055b50(int a, void *b);
extern int func_020b9eec(void *a, void *b, int c);
extern void *func_021077e8(void *a);
extern void *func_02107828(void *a);
extern void *func_02056268(void *a, void *b);
extern int NNS_G3dBindMdlTex(void *a, void *b);
extern int NNS_G3dBindMdlPltt(void *a, void *b);
extern int func_020561cc(int, int);

UnkStruct_02055b00 *func_02055b00(UnkStruct_02055b00 *ptr)
{
    ptr->data = data_020dd10c;
    func_020ba01c(ptr->sub);
    ptr->unk_04 = 0;
    ptr->unk_08 = 0;
    ptr->unk_0C = 0;
    ptr->unk_10 = 0;
    ptr->unk_30 = 0;
    ptr->unk_31 = 0;
    return ptr;
}

void func_02055af4(int *out)
{
    *out = (int) ((int *) data_020dd10c);
}

void *func_02055adc(void *self)
{
    Object *obj = (Object *) self;
    obj->vtable = (void *) ((unsigned char *) data_020dd10c);
    func_020edb3c(self);
    return (char *) self + 0;
}

void func_02055aac(void *self)
{
    if (*(int *) ((char *) self + 4) != 0) {
        func_020e993c(*(void **) ((char *) self + 8), *(int *) ((char *) self + 4));
    }
    *(int *) ((char *) self + 4) = 0;
    *(int *) ((char *) self + 8) = 0;
    *(int *) ((char *) self + 0xc) = 0;
    *(int *) ((char *) self + 0x10) = 0;
    *(char *) ((char *) self + 0x30) = 0;
    func_020b9ec4((char *) self + 0x14);
}

u8 func_020559d0(UnkStruct_020559d0 *s, int a1, int a2, int a3, void *a4)
{
    void *p = a4;
    u8 state = s->unk_30;
    void *p2;
    u8 *q;
    unsigned int flag;

    if (state == 3) {
        return state;
    }

    if (p == 0) {
        p = data_021fbe94;
    }

    if (state == 0) {
        s->unk_04 = func_02064b2c(a1, p, ~3, 0);
        s->unk_08 = p;
        p2 = func_021077e8(s->unk_04);
        func_02055b50(a2, p2);
        func_020b9eec(&s->unk_14, p2, 1);
        s->unk_30 = 1;
        return s->unk_30;
    }

    if (state == 1) {
        flag = (s->unk_21 == 2) ? 1u : 0u;
        if (flag == 0) {
            return state;
        }
        s->unk_30 = 2;
    }

    if (s->unk_30 == 2) {
        q = (u8 *) func_02107828(s->unk_04);
        q = q + *(u32 *) (q + *(u16 *) (q + 0xe) + 0xc);
        s->unk_0C = func_02056268(q, (void *) a3);
        p2 = func_021077e8(s->unk_04);
        NNS_G3dBindMdlTex(s->unk_0C, p2);
        NNS_G3dBindMdlPltt(s->unk_0C, p2);
        func_020e993c(s->unk_08, (int) s->unk_04);
        s->unk_08 = 0;
        s->unk_04 = 0;
        s->unk_30 = 3;
    }

    return s->unk_30;
}

int func_02055954(UnkStruct_02055954 *self, int arg2, int arg3, int arg4)
{
    u8 state = self->unk_30;
    if (state == 3) {
        return state;
    }
    if (state == 0) {
        func_02055b50(arg3, (void *) arg2);
        func_020b9eec(self->unk_14, (void *) arg2, 1);
        self->unk_30 = 1;
        return self->unk_30;
    }
    if (state == 1) {
        unsigned int flag = (self->unk_21 == 2) ? 1 : 0;
        if (flag != 0) {
            self->unk_30 = 2;
        } else {
            return state;
        }
    }
    if (self->unk_30 == 2) {
        self->unk_10 = func_020561cc(arg2, arg4);
        self->unk_30 = 3;
    }
    return self->unk_30;
}

int func_02055950(int *p0)
{
    return p0[3];
}

int func_0205594c(int *p0)
{
    return p0[4];
}
