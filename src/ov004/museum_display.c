/* museum_display: 15 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f34c @ 0x0222f34c, 0x1c bytes, Thumb
 * func_ov004_0222f334 @ 0x0222f334, 0x18 bytes, Thumb
 * func_ov004_0222f320 @ 0x0222f320, 0x14 bytes, Thumb
 * func_ov004_0222f304 @ 0x0222f304, 0x1c bytes, Thumb
 * func_ov004_0222f2f4 @ 0x0222f2f4, 0x10 bytes, Thumb
 * func_ov004_0222f2dc @ 0x0222f2dc, 0x18 bytes, Thumb
 * func_ov004_0222f2c4 @ 0x0222f2c4, 0x18 bytes, Thumb
 * func_ov004_0222f2a4 @ 0x0222f2a4, 0x20 bytes, Thumb
 * func_ov004_0222f270 @ 0x0222f270, 0x34 bytes, Thumb
 * func_ov004_0222f26c @ 0x0222f26c, 0x4 bytes, Thumb
 * func_ov004_0222f258 @ 0x0222f258, 0x14 bytes, Thumb
 * func_ov004_0222f248 @ 0x0222f248, 0x10 bytes, Thumb
 * func_ov004_0222f234 @ 0x0222f234, 0x14 bytes, Thumb
 * func_ov004_0222f1b4 @ 0x0222f1b4, 0x80 bytes, Thumb
 * func_ov004_0222f17c @ 0x0222f17c, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char b[16];
} UnkStruct_0222f320;

typedef struct {
    char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0222f304;

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0222f304_2;

typedef struct {
    UnkStruct_0222f304 *unk_00;
    UnkStruct_0222f304_2 *unk_04;
} UnkStruct_0222f304_3;

struct _Obj {
    void *vtbl;
};

typedef u16 (*Fn)(int);

typedef struct {
    int unk_00;
    unsigned int unk_04;
} UnkStruct_0222f17c;

extern int func_020edf70(unsigned int size);
extern UnkStruct_0222f320 data_ov004_022478a8[];
extern void *func_ov004_0222c87c(void *arg);
extern int data_ov004_02255200;
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern int func_ov004_0222c600(void *self, int a, int b);
extern void func_02055dc8(void *p, void *fn, void *self);
extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(char *parameter0);
extern void *func_020e9948(void *, int);
extern void *data_021c9b24;
extern int func_02071298(void *, u16 *);
extern int func_02064328(void *, void *, int, int);
extern u8 func_0205790c(int, void *);
extern int data_021f38f8;
extern int data_ov004_02258460;
extern int data_ov004_02255268;

void *func_ov004_0222f2dc(void *arg);
int func_ov004_0222f234(char *self, int a1, char *a2);
void func_ov004_0222f1b4(char *self);
int func_ov004_0222f17c(u8 *self, int c);

void func_ov004_0222f34c(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_020edf70(0x294)))) {
        func_ov004_0222f2dc((void *) conditionInput0);
    }
}

u16 func_ov004_0222f334(unsigned int i)
{
    unsigned int v;
    if (i < 0x14) {
        v = i * 4 + 0x3894;
    } else {
        v = 0x3894;
    }
    return (u16) v;
}

UnkStruct_0222f320 *func_ov004_0222f320(unsigned int i)
{
    if (i < 2) {
        return &data_ov004_022478a8[i];
    }
    return data_ov004_022478a8;
}

void func_ov004_0222f304(UnkStruct_0222f304_3 *s)
{
    void *t = s->unk_04->unk_2C;
    if (t != 0) {
        func_ov004_0222f234((char *) t, (unsigned char) s->unk_00->unk_01, (char *) s);
    }
}

void func_ov004_0222f2f4(char *self)
{
    *(void **) (self + 0x14) = (void *) (void (*)(void *)) func_ov004_0222f304;
    *(u8 *) (self + 0x8e) = 2;
}

void *func_ov004_0222f2dc(void *arg)
{
    func_ov004_0222c87c(arg);
    *(void **) arg = &data_ov004_02255200;
    return arg;
}

void *func_ov004_0222f2c4(void *arg)
{
    *((void **) arg) = &data_ov004_02255200;
    func_ov004_0222c7a0(arg);
    return arg;
}

void *func_ov004_0222f2a4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255200);
    func_ov004_0222c7a0(obj);
    func_020edf54(obj);
    return obj;
}

int func_ov004_0222f270(void *self)
{
    void *p;

    p = (void *) func_ov004_0222f320((unsigned int) (*(void **) ((char *) self + 8)));
    func_ov004_0222c600(self, *(int *) ((char *) p + 8), *(int *) ((char *) p + 0xc));
    func_02055dc8((char *) self + 0xec, (void *) func_ov004_0222f2f4, self);
    func_ov004_0222f1b4((char *) self);
    return 1;
}

int func_ov004_0222f26c(void)
{
    return 1;
}

int func_ov004_0222f258(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    return 0x1;
}

int func_ov004_0222f248(char *arg0)
{
    func_ov004_0222c598((char *) arg0);
    return 1;
}

int func_ov004_0222f234(char *self, int a1, char *a2)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0222f17c((u8 *) ((void *) ((void *) (self))), (int) ((int) (a1)));
    *(int *) ((char *) *(int *) (a2 + 0xb8)) = v1;
    return v1;
}

void func_ov004_0222f1b4(char *self)
{
    int flag = 0;
    u16 t;
    unsigned i;
    char *m = (char *) func_ov004_0222f320((unsigned int) (*(void **) (self + 8)));
    *(void **) (self + 0x290) = func_020e9948(data_021c9b24, *(int *) (m + 4));
    for (i = 0; i < *(unsigned *) (m + 4); i++) {
        int f;
        t = (*(Fn *) m)(i);
        f = flag;
        if (func_02071298(&data_021f38f8, &t) != 0) {
            f = 1;
        }
        func_02064328(&data_ov004_02258460, &data_ov004_02255268, i, f);
        *(*(u8 **) (self + 0x290) + i) = func_0205790c(*(int *) (self + 0x148), &data_ov004_02258460);
    }
}

int func_ov004_0222f17c(u8 *self, int c)
{
    unsigned int i, n;
    UnkStruct_0222f17c *p;
    p = (UnkStruct_0222f17c *) func_ov004_0222f320((unsigned int) (*(void **) (self + 8)));
    i = 0;
    n = p->unk_04;
    while (i < n) {
        if (c == (*(signed char **) (self + 0x290))[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
