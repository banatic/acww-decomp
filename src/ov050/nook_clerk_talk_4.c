/* nook_clerk_talk_4: 21 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02262bac @ 0x02262bac, 0x3c bytes, Thumb
 * func_ov050_02262b58 @ 0x02262b58, 0x54 bytes, Thumb
 * func_ov050_02262b08 @ 0x02262b08, 0x50 bytes, Thumb
 * func_ov050_02262ad8 @ 0x02262ad8, 0x30 bytes, Thumb
 * func_ov050_02262acc @ 0x02262acc, 0xc bytes, Thumb
 * func_ov050_02262ab8 @ 0x02262ab8, 0x14 bytes, Thumb
 * func_ov050_02262a28 @ 0x02262a28, 0x90 bytes, Thumb
 * func_ov050_022629ec @ 0x022629ec, 0x3c bytes, Thumb
 * func_ov050_02262970 @ 0x02262970, 0x7c bytes, Thumb
 * func_ov050_02262910 @ 0x02262910, 0x60 bytes, Thumb
 * func_ov050_022628c8 @ 0x022628c8, 0x48 bytes, Thumb
 * func_ov050_0226288c @ 0x0226288c, 0x3c bytes, Thumb
 * func_ov050_02262850 @ 0x02262850, 0x3c bytes, Thumb
 * func_ov050_022627d4 @ 0x022627d4, 0x7c bytes, Thumb
 * func_ov050_02262798 @ 0x02262798, 0x3c bytes, Thumb
 * func_ov050_02262734 @ 0x02262734, 0x64 bytes, Thumb
 * func_ov050_02262700 @ 0x02262700, 0x34 bytes, Thumb
 * func_ov050_022626c8 @ 0x022626c8, 0x38 bytes, Thumb
 * func_ov050_0226265c @ 0x0226265c, 0x6c bytes, Thumb
 * func_ov050_02262628 @ 0x02262628, 0x32 bytes, Thumb
 * func_ov050_02262618 @ 0x02262618, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02262b08 {
    unsigned char pad_00[0xD0];
    int unk_D0;
};

typedef struct {
    char pad_00[0xb4];
    char *arr;
    char pad_B8[0xd0 - 0xb4 - 4];
    int val;
} UnkStruct_02262ad8;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    void *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_02262a28;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    char *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_02262970;

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0xb4 - 0x1f];
    unsigned char *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    unsigned int unk_D0;
} SelfType;

typedef struct {
    char pad_00[0xb4];
    unsigned char *ptr;
} ObjA;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    unsigned char *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_022627d4;

typedef struct {
    int data[9];
} Local2;

struct Arg0 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[140];
    int unk_D0;
};

typedef struct {
    int data[8];
} UnkStruct_02262734;

struct UnkStruct_0226265c {
    u8 pad_00[0xd0];
    u32 unk_D0;
};

typedef struct {
    char pad_00[0xb4];
    void *unk_B4;
} FuncOvlStruct;

extern int func_0209a000(void *, int);
extern void func_0209abd0(int);
extern int func_020154b4(void *, unsigned short *, int, int, int);
extern int func_0209b4d4(void *argument0);
extern int func_0209bd44(int);
extern int func_0209bc40(int);
extern void func_0209bb90(int, int);
extern unsigned char func_02099f1c(void *dst, int (*predicate)(unsigned short *));
extern int func_0209ad9c(int a, int b);
extern void func_0209abc8(int a);
extern int func_ov050_022634b4(unsigned short *value);
extern void func_ov050_02263408(void *a);
extern void func_0209ab94(int b);
extern void func_0209abc0(int x);
extern int func_020984e8(void);
extern void func_0209ab78(int);
extern int func_02099fe8(void);
extern void *func_02094fd4(void *p);
extern void func_0209ab34(void *p);
extern void func_02068404(int a, int b, void *c);
extern void *func_02094fbc(void *p);
extern void func_0209aacc(int);
extern int func_0209b4cc(int, int);
extern int func_02003618(int, void *);
extern void func_0206844c(unsigned int, unsigned int, int);
extern unsigned char data_021f43e8[];
extern void func_0209a934(void *arg);
extern int func_0209ac50(void *arg1, void *arg2, unsigned short *arg3);
extern void func_0209a918(void *);
extern int func_0209a8fc(void *);
extern char data_021dc7a8[];
extern char data_021ebcd4[];
extern int func_02060d3c(char *ptr);
extern void func_02060d24(char *ptr, int val);
extern void func_02015fb0(void *self, int val, int arg2, int arg3, int arg4, int arg5);
extern void func_0209a8a4(int);
extern void func_02098fd0(int, int);
extern int func_02099670(int);
extern int func_0208602c(void);
extern void func_020860f0(int, int);
extern void func_02088be0(int);
void func_ov050_02264834(void *arg0, int arg1);

void func_ov050_02262bac(int *a, int b)
{
    unsigned short local = 0x11a8;
    if (func_0209a000(&local, 0)) {
        func_0209abd0(b);
        a[52] = 3;
    } else {
        a[52] = 1;
    }
}

void func_ov050_02262b58(void *a, int b)
{
    unsigned short h = 0x11a8;
    int v;

    func_020154b4(a, &h, 0, 5, 0);
    *(int *) ((char *) a + 0xd0) = 6;

    v = func_0209b4d4((void *) (void *) func_0209ad9c(b, 0));
    if (func_0209bd44(v) != 0) {
        if (func_0209bc40(v) == 0xb) {
            func_0209bb90(v, 1);
        }
    }
}

void func_ov050_02262b08(struct UnkStruct_02262b08 *param0, int param1)
{
    unsigned char buf[4];
    int result;

    func_02099f1c(buf, func_ov050_022634b4);
    if (buf[2] >= 7) {
        param0->unk_D0 = 8;
    } else {
        param0->unk_D0 = 9;
    }
    result = func_0209b4d4((void *) (func_0209ad9c(param1, 0)));
    func_0209abc8(param1);
    func_0209bb90(result, 2);
}

void func_ov050_02262ad8(UnkStruct_02262ad8 *a, int b)
{
    func_ov050_02263408(a);
    func_0209ab94(b);
    a->arr[0x73e] = 0;
    a->val = 0xa;
}

void func_ov050_02262acc(int a, int b)
{
    func_0209abc0(b);
}

void func_ov050_02262ab8(int a, int b)
{
    func_020984e8();
    func_0209ab78(b);
}

void func_ov050_02262a28(UnkStruct_02262a28 *a, void *p1)
{
    short w;
    int local2[9];
    int ret;

    ret = func_0209b4d4((void *) (func_0209ad9c((int) p1, 0)));
    if (func_0209bd44(ret) != 0) {
        if (func_0209bc40(ret) == 0xd) {
            func_0209bb90(ret, 1);
        }
    }
    if (func_02099fe8() >= 0) {
        func_02094fd4(local2);
        func_0209ab34(p1);
        w = 0x1563;
        func_0209ac50(p1, local2, (unsigned short *) (&w));
        func_02068404(a->unk_40, 1, local2);
        ((char *) a->unk_B4)[0x73e] = 0;
        a->unk_D0 = 0x18;
        func_02094fbc(local2);
    } else {
        a->unk_D0 = 0x17;
    }
}

void func_ov050_022629ec(void *param, int event)
{
    int zero;
    unsigned short arr[2];

    arr[0] = 0x1563;
    if (func_0209a000((void *) arr, 2) == 0) {
        return;
    }
    arr[1] = 0x1563;
    zero = 0;
    func_020154b4(param, &arr[1], 2, 5, zero);
}

void func_ov050_02262970(UnkStruct_02262970 *self, int arg1)
{
    char buf[0x20];
    int v;

    v = func_0209ad9c(arg1, 0);
    if (((void) (func_0209bb90(func_0209b4d4((void *) v), 1)), func_02099fe8()) >= 0) {
        func_0209aacc(arg1);
        v = func_0209b4cc(v, 1);
        if (v != 0) {
            func_02094fd4(buf);
            func_02003618(v, buf);
            func_02068404(self->unk_40, 0, buf);
            func_02094fbc(buf);
        }
        self->unk_B4[0x73e] = 0;
        self->unk_D0 = 0x1f;
    } else {
        self->unk_D0 = 0x17;
    }
}

void func_ov050_02262910(SelfType *self, int event)
{
    int sp_arg;
    unsigned short local[2];

    local[0] = 0x1020;
    if (func_0209a000(&local[0], 0)) {
        local[1] = 0x1020;
        sp_arg = 0;
        func_020154b4(self, (unsigned short *) (&local[1]), 0, 5, sp_arg);
    }
    if (self->unk_1E == 0x1f) {
        self->unk_D0 = 0x20;
        self->unk_B4[0x73e] = 2;
    } else {
        self->unk_D0 = 0x26;
    }
}

void func_ov050_022628c8(unsigned int *param, int event)
{
    if (((unsigned char *) *((unsigned int *) ((char *) param + 0xb4)))[0x73e] == 0 && func_02099fe8() != -1) {
        *(unsigned int *) ((char *) param + 0xd0) = 0x22;
        return;
    }
    ((unsigned char *) *((unsigned int *) ((char *) param + 0xb4)))[0x73e] = 1;
    func_0206844c(*(unsigned int *) ((char *) param + 0x40), (unsigned int) data_021f43e8, 0);
}

void func_ov050_0226288c(ObjA *a, void *b)
{
    func_0209bb90(func_0209b4d4((void *) (func_0209ad9c((int) b, 0))), 0);
    a->ptr[0x73e] = 1;
    func_ov050_02262910((SelfType *) a, (int) b);
}

void func_ov050_02262850(int param1, int param2)
{
    int res;

    res = func_0209ad9c(param2, 0);
    res = func_0209b4d4((void *) res);
    res = (func_0209bb90(res, 0), (int) res);
    if (func_02099fe8() >= 0) {
        *(int *) ((char *) param1 + 0xd0) = 0x25;
    } else {
        func_0206844c(*(int *) ((char *) param1 + 0x40), (unsigned int) (((int *) data_021f43e8)), 0);
    }
}

void func_ov050_022627d4(UnkStruct_022627d4 *a, void *b)
{
    unsigned short local1;
    Local2 local2;
    int r6;

    r6 = func_0209b4d4((void *) (func_0209ad9c((int) b, 0)));
    func_02094fd4(&local2);
    func_0209bb90(r6, 2);
    a->unk_B4[0x73e] = 0;
    if (func_02099fe8() >= 0) {
        func_0209a934(b);
        local1 = 0x1561;
        func_0209ac50(b, &local2, &local1);
        func_02068404(a->unk_40, 1, &local2);
        a->unk_D0 = 0x29;
    } else {
        a->unk_D0 = 0x17;
    }
    func_02094fbc(&local2);
}

void func_ov050_02262798(void *param, int event)
{
    unsigned short local[2];
    local[0] = 0x1561;
    if (func_0209a000((void *) local, 2)) {
        local[1] = 0x1561;
        func_020154b4(param, (unsigned short *) (&local[1]), 0, 5, 0);
    }
}

void func_ov050_02262734(struct Arg0 *arg0, void *arg1)
{
    unsigned short id[2];
    UnkStruct_02262734 local;
    id[0] = 0x1564;
    if (func_0209a000((void *) id, 2)) {
        func_02094fd4(&local);
        func_0209a918(arg1);
        id[1] = 0x1564;
        func_0209ac50(arg1, &local, &id[1]);
        func_02068404(arg0->unk_40, 1, &local);
        arg0->unk_D0 = 0x2e;
        func_02094fbc(&local);
    } else {
        arg0->unk_D0 = 0x17;
    }
}

void func_ov050_02262700(void *p, int event)
{
    int zero;
    unsigned short hw;
    hw = 0x1564;
    zero = 0;
    func_020154b4(p, &hw, 2, 5, zero);
    *((char *) ((char *) *(char **) ((char *) p + 0xb4) + 0x73e)) = 0;
}

void func_ov050_022626c8(void *a, void *b)
{

    func_0209bb90(func_0209b4d4((void *) (void *) func_0209ad9c((int) b, 0)), 2);
    func_0209a8fc(b);
    *(char *) (*(char **) ((char *) a + 0xB4) + 0x73E) = 0;
}

void func_ov050_0226265c(struct UnkStruct_0226265c *self, int event)
{
    int res1, res2, val;
    char *base, *other;
    base = data_021dc7a8;
    other = data_021ebcd4;
    res1 = func_02060d3c(other);
    if (res1 < 0x579) {
        self->unk_D0 = 0x36;
        return;
    }
    res2 = func_02060d3c(other);
    func_02060d24(other, res2 - 0x578);
    val = func_02060d3c(base + 0xf52c);
    func_02015fb0(self, val, 2, 10, 0, 0);
    self->unk_D0 = 0x34;
}

void func_ov050_02262628(int p0, int p1)
{
    int b, c, d;
    func_0209a8a4(p1);
    b = func_020984e8();
    func_02098fd0(b, 1);
    c = func_02099670(b);
    d = func_0208602c();
    func_020860f0(d, 5);
    func_02088be0(c);
}

void func_ov050_02262618(FuncOvlStruct *self, int event)
{
    func_ov050_02264834(self->unk_B4, 0x11);
}
