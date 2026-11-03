/* nook_clerk_talk_5: 11 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_022634b4 @ 0x022634b4, 0x14 bytes, Thumb
 * func_ov050_02263408 @ 0x02263408, 0xac bytes, Thumb
 * func_ov050_02263394 @ 0x02263394, 0x74 bytes, Thumb
 * func_ov050_02263258 @ 0x02263258, 0x13c bytes, Thumb
 * func_ov050_0226310c @ 0x0226310c, 0x14c bytes, Thumb
 * func_ov050_02263084 @ 0x02263084, 0x88 bytes, Thumb
 * func_ov050_02263028 @ 0x02263028, 0x5c bytes, Thumb
 * func_ov050_02262f48 @ 0x02262f48, 0xe0 bytes, Thumb
 * func_ov050_02262eec @ 0x02262eec, 0x5c bytes, Thumb
 * func_ov050_02262e90 @ 0x02262e90, 0x5c bytes, Thumb
 * func_ov050_02262e34 @ 0x02262e34, 0x5c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02263258 {
    unsigned char pad_00[4];
    unsigned char state;
};

typedef struct {
    u8 pad_00[0xb4];
    u8 *ptr;
} FieldHolder;

typedef struct {
    unsigned char pad_00[0xb4];
    void *ptr;
} FieldHolder_02263084;

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char *arr;
} UnkStruct_02263028;

struct UnkStruct_02262f48_3 {
    unsigned char pad_00[0x73e];
    unsigned char unk_73E;
};

struct UnkStruct_02262f48 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x70];
    struct UnkStruct_02262f48_3 *unk_B4;
};

struct UnkStruct_02262f48_2 {
    unsigned char pad_00[4];
    unsigned char unk_04;
};

typedef struct {
    char pad_00[0xb4];
    unsigned char *ptr;
} Arg0;

typedef struct {
    char pad_00[4];
    unsigned char flag;
} Arg1;

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char *array;
} P0Struct;

typedef struct {
    unsigned char pad_00[4];
    unsigned char mode;
} P1Struct;

extern int func_020644cc(int);
extern int func_0209a000(void *, int);
extern int func_020154b4(void *, void *, int, int, int);
extern int func_02099640(int argument0);
extern int func_0209abb0(void *argument0);
extern void *func_02099710(void *p);
extern int func_0204bcdc(void *argument0);
extern int func_0204bc64(void *p);
extern int func_020984e8(void);
extern int func_0209ad9c(int r0, int r1);
extern void *func_0209b4d4(void *object);
extern int func_02099fe8(void);
extern int func_0209bc40(void *p);
extern int func_0209b414(int r0);
extern unsigned char func_02099f1c(void *dst, void *src);
extern int func_02099e9c(void *p);
extern void func_0209abd0(int r0);
extern int func_02099020(void *a, int b);
extern void *func_02099870(void *a);
extern int func_0207a5d0(void *a, void *b);
extern u16 *func_020992e4(int argument0);
extern void func_0209bb90(void *a, int b);
extern unsigned char data_021e5a2c[];
extern void *func_0209b4cc(void *a, int b);
extern void *func_02094fd4(void *local);
extern int func_0209bba0(void *handle);
extern int func_02003618(void *h, void *local);
extern void func_02068404(void *a, int b, void *local);
extern void *func_02094fbc(void *local);

int func_ov050_022634b4(unsigned short *p)
{
    if (*p == 0xfff1) {
        return 1;
    }
    return 0;
}

void func_ov050_02263408(void *arg)
{
    unsigned short a, b, c, d, e, f;
    int i;

    a = (unsigned short) (func_020644cc(3) + 0x14fe);
    func_0209a000(&a, 0);

    b = (unsigned short) (func_020644cc(3) + 0x1504);
    func_0209a000(&b, 0);

    c = (unsigned short) (func_020644cc(3) + 0x150a);
    func_0209a000(&c, 0);

    d = (unsigned short) (func_020644cc(3) + 0x1510);
    func_0209a000(&d, 0);

    for (i = 0; i < 3; i++) {
        e = 0x151d;
        func_0209a000(&e, 0);
    }

    f = 0x151d;
    func_020154b4(arg, &f, 0, 5, 0);
}

int func_ov050_02263394(void *p0, unsigned char *p1)
{
    void *obj;
    void *r4;
    int matched;

    obj = (void *) func_020984e8();

    if (!func_0209abb0((void *) func_02099640((int) obj))) {
        goto fail;
    }
    if (!obj) {
        goto fail;
    }

    r4 = func_02099710(obj);
    if (func_0204bcdc(r4)) {
        unsigned short local = 0x11a8;
        int a = func_0204bc64(r4);
        int b = func_0204bc64(&local);
        matched = (a == b);
    } else {
        matched = (*(unsigned short *) r4 == 0x11a8);
    }
    if (matched) {
        goto fail;
    }
    p1[4] = 0xe;
    return 1;
fail:
    return 0;
}

void func_ov050_02263258(void *a, struct UnkStruct_02263258 *b)
{
    int r7;
    int local0;
    int local1;
    void *r4;
    unsigned short buf[4];
    unsigned int local2;
    int temp;

    r7 = func_020984e8();
    local0 = func_02099640(r7);
    local1 = func_0209ad9c(local0, 0);
    r4 = func_0209b4d4((void *) local1);
    func_02099fe8();

    if (func_0209bc40(r4) == 0xb && (unsigned int) func_0209bba0(r4) >= 1 && func_0209b414(local1) != 0) {
        if (func_ov050_02263394(a, (unsigned char *) b) == 0) {
            func_02099f1c(&local2, (void *) (int (*)(void *)) func_ov050_022634b4);
            if (((unsigned char *) &local2)[2] >= 7) {
                b->state = 8;
            } else {
                b->state = 9;
            }
        }
        return;
    }

    if (func_0209bc40(r4) == 0xb && (unsigned int) func_0209bba0(r4) >= 1) {
        r4 = func_02099710((void *) r7);
        if (func_0204bcdc(r4) != 0) {
            buf[3] = 0x11a8;
            r4 = (void *) func_0204bc64(r4);
            if (r4 == (void *) func_0204bc64(&buf[3])) {
                temp = 1;
            } else {
                temp = 0;
            }
        } else {
            if (*(unsigned short *) r4 == 0x11a8) {
                temp = 1;
            } else {
                temp = 0;
            }
        }
        if (temp != 0) {
            b->state = 7;
            return;
        }

        buf[0] = 0x11a8;
        if (func_02099e9c(buf) < 0) {
            temp = 1;
        } else {
            temp = 0;
        }
        if (temp != 0) {
            buf[1] = 0x11a8;
            if (func_0209a000(&buf[1], 0) != 0) {
                b->state = 4;
                return;
            } else {
                b->state = 2;
                return;
            }
        } else {
            b->state = 5;
            return;
        }
    } else {
        buf[2] = 0x11a8;
        if (func_0209a000(&buf[2], 0) != 0) {
            func_0209abd0(local0);
            b->state = 3;
            return;
        } else {
            b->state = 1;
            return;
        }
    }
}

void func_ov050_0226310c(void *p0, void *p1)
{
    void *h;
    void *x;
    volatile int v[5];
    u16 arr[5];
    u16 *ptr2;
    u16 *q;
    int i;
    h = (void *) func_020984e8();
    x = (void *) func_0209ad9c((int) ((void *) func_02099640((int) h)), 0);
    ptr2 = &arr[0];
    x = func_0209b4d4(x);
    func_02099fe8();
    if (func_ov050_02263394(p0, (unsigned char *) p1) != 0) {
        return;
    }
    i = 0;
    q = (u16 *) ((unsigned int) arr);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    v[3] = 0;
    v[4] = 0;
    for (; i < 3; i++) {
        q[0] = 0x151d;
        if (((func_02099e9c((void *) ptr2) >= 0) ? (1) : (v[0])) == 0) {
            q[1] = (u16) (0x14fe + i);
            if (((func_02099e9c((void *) (&arr[1])) >= 0) ? (1) : (v[1])) == 0) {
                q[2] = (u16) (0x1504 + i);
                if (((func_02099e9c((void *) (&arr[2])) >= 0) ? (1) : (v[2])) == 0) {
                    q[3] = (u16) (0x150a + i);
                    if (((func_02099e9c((void *) (&arr[3])) >= 0) ? (1) : (v[3])) == 0) {
                        q[4] = (u16) (0x1510 + i);
                        if (((func_02099e9c((void *) (&arr[4])) >= 0) ? (1) : (v[4])) == 0) {
                            continue;
                        }
                    }
                }
            }
        }
        ((u8 *) p1)[4] = (u8) (((FieldHolder *) p0)->ptr[0x73e] + 0xf);
        ((FieldHolder *) p0)->ptr[0x73e] = 1;
        return;
    }

    ((FieldHolder *) p0)->ptr[0x73e] = 1;
    if ((func_02099020(h, 0xa) != 0) && (func_0207a5d0((void *) data_021e5a2c, func_02099870(h)) != 0)) {

        if ((*func_020992e4((int) (void *) func_020984e8())) != 0) {
            func_0209bb90(x, 1);
            ((u8 *) p1)[4] = 0x1a;
            return;
        }
    }
    ((u8 *) p1)[4] = 0x11;
}

void func_ov050_02263084(void *p0, void *p1)
{
    void *r6;

    r6 = (void *) func_020984e8();

    func_0209b4d4((void *) (void *) func_0209ad9c((int) ((void *) func_02099640((int) r6)), 0));
    func_02099fe8();

    if (func_ov050_02263394(p0, (unsigned char *) p1) != 0) {
        return;
    }

    if (!(func_02099020(r6, 0xa) != 0 && func_0207a5d0((void *) data_021e5a2c, func_02099870(r6)) != 0)) {
        if (*((unsigned char *) (((FieldHolder_02263084 *) p0)->ptr) + 0x73e) != 0) {
            ((unsigned char *) p1)[4] = 0x13;
        } else {
            ((unsigned char *) p1)[4] = 0x14;
        }
        return;
    }

    if (*(unsigned short *) (unsigned short *) func_020992e4((int) ((void *) func_020984e8())) == 0) {
        ((unsigned char *) p1)[4] = 0x15;
    } else {
        ((unsigned char *) p1)[4] = 0x16;
    }
}

void func_ov050_02263028(UnkStruct_02263028 *self, unsigned char *dst)
{
    if (func_ov050_02263394(self, (unsigned char *) dst) != 0) {
        return;
    }
    if (func_0209bba0((void *) ((int) func_0209b4d4((void *) (func_0209ad9c(func_02099640(func_020984e8()), 0))))) == 1) {
        dst[4] = 0x1e;
    } else {
        if (self->arr[0x73e] == 0) {
            dst[4] = 0x1c;
            self->arr[0x73e] = 1;
        } else {
            dst[4] = 0x10;
        }
    }
}

void func_ov050_02262f48(struct UnkStruct_02262f48 *self, struct UnkStruct_02262f48_2 *status)
{
    char local[0x24];
    void *handle;
    void *handle2;

    if (func_ov050_02263394((void *) self, (unsigned char *) status) != 0) {
        return;
    }

    handle = (void *) func_0209ad9c((int) ((void *) func_02099640((int) func_020984e8())), 0);
    handle2 = func_0209b4d4((void *) handle);
    handle = func_0209b4cc(handle, 1);
    func_02094fd4(local);

    if (func_0209bba0(handle2) == 2) {
        status->unk_04 = 0x28;
        func_02094fbc(local);
        return;
    }
    if (func_0209bba0(handle2) == 0) {
        if (self->unk_B4->unk_73E == 0 || self->unk_B4->unk_73E == 2) {
            if (handle != 0) {
                func_02003618(handle, local);
                func_02068404(self->unk_40, 0, local);
            }
            status->unk_04 = 0x21;
            if (self->unk_B4->unk_73E == 2) {
                self->unk_B4->unk_73E = 1;
            }
        } else {
            status->unk_04 = 0x10;
        }
        func_02094fbc(local);
        return;
    }
    if (func_0209bba0(handle2) == 1) {
        if (handle != 0) {
            func_02003618(handle, local);
            func_02068404(self->unk_40, 0, local);
        }
        status->unk_04 = 0x27;
        func_02094fbc(local);
        return;
    }
    func_02094fbc(local);
}

void func_ov050_02262eec(Arg0 *arg0, Arg1 *arg1)
{
    if (func_ov050_02263394(arg0, (unsigned char *) arg1) != 0) {
        return;
    }

    if (func_0209bba0((void *) func_0209b4d4((void *) (void *) func_0209ad9c(func_02099640((int) func_020984e8()), 0))) == 1) {
        arg1->flag = 0x2c;
    } else {
        if (arg0->ptr[0x73e] == 0) {
            arg1->flag = 0x2b;
            arg0->ptr[0x73e] = 1;
        } else {
            arg1->flag = 0x10;
        }
    }
}

void func_ov050_02262e90(void *a0, void *a1)
{
    if (func_ov050_02263394(a0, (unsigned char *) a1) != 0) {
        return;
    }

    if (func_0209bba0((void *) func_0209b4d4((void *) (void *) func_0209ad9c(func_02099640((int) func_020984e8()), 0))) == 1) {
        ((u8 *) a1)[4] = 0x31;
        return;
    }
    if (((u8 *) *(u8 **) ((u8 *) a0 + 0xb4))[0x73e] == 0) {
        ((u8 *) a1)[4] = 0x2b;
        *(u8 *) (*(u8 **) ((u8 *) a0 + 0xb4) + 0x73e) = 1;
    } else {
        ((u8 *) a1)[4] = 0x10;
    }
}

void func_ov050_02262e34(P0Struct *p0, P1Struct *p1)
{
    int r;
    if (func_ov050_02263394(p0, (unsigned char *) p1) != 0) {
        return;
    }
    r = func_020984e8();
    r = func_02099640(r);
    r = func_0209ad9c(r, 0);
    r = (int) func_0209b4d4((void *) r);
    r = func_0209bba0((void *) r);
    if (r == 1) {
        p1->mode = 0x33;
        return;
    }
    if (p0->array[0x73e] == 0) {
        p1->mode = 0x32;
        p0->array[0x73e] = 1;
        return;
    }
    p1->mode = 0x10;
}
