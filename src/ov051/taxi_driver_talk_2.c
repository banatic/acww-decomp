/* taxi_driver_talk_2: 16 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_02260f2c @ 0x02260f2c, 0x68 bytes, Thumb
 * func_ov051_02260f04 @ 0x02260f04, 0x28 bytes, Thumb
 * func_ov051_02260ec0 @ 0x02260ec0, 0x44 bytes, Thumb
 * func_ov051_02260ea0 @ 0x02260ea0, 0x20 bytes, Thumb
 * func_ov051_02260e2c @ 0x02260e2c, 0x74 bytes, Thumb
 * func_ov051_02260e08 @ 0x02260e08, 0x22 bytes, Thumb
 * func_ov051_02260de4 @ 0x02260de4, 0x22 bytes, Thumb
 * func_ov051_02260dc0 @ 0x02260dc0, 0x22 bytes, Thumb
 * func_ov051_02260d94 @ 0x02260d94, 0x2c bytes, Thumb
 * func_ov051_02260d44 @ 0x02260d44, 0x50 bytes, Thumb
 * func_ov051_02260d1c @ 0x02260d1c, 0x28 bytes, Thumb
 * func_ov051_02260cd8 @ 0x02260cd8, 0x44 bytes, Thumb
 * func_ov051_02260c94 @ 0x02260c94, 0x44 bytes, Thumb
 * func_ov051_02260c44 @ 0x02260c44, 0x50 bytes, Thumb
 * func_ov051_02260c1c @ 0x02260c1c, 0x28 bytes, Thumb
 * func_ov051_02260b60 @ 0x02260b60, 0xbc bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_02260f2c;

typedef struct UnkStruct_02260f2c_2 {
    unsigned char pad_00[0xb4];
    UnkStruct_02260f2c v;
} UnkStruct_02260f2c_2;

struct UnkStruct_02260f04 {
    char pad_00[0x40];
    unsigned int unk_40;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260ec0;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
} Param;

typedef struct {
    char pad_00[0x40];
    unsigned int unk_40;
} UnkStruct_02260d94;

struct UnkStruct_02260d44 {
    char pad_00[0x40];
    unsigned int unk_40;
};

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02260d1c;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260cd8;

struct UnkStruct_02260c94 {
    unsigned char pad_00[0x40];
    void *unk_40;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260c1c;

typedef struct UnkStruct_02260b60_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02260b60_2;

typedef struct UnkStruct_02260b60 {
    u8 a;
    u8 b;
    u16 c;
} UnkStruct_02260b60;

typedef struct Row2 {
    UnkStruct_02260b60 e[2];
} Row2;

typedef struct Row {
    int w[2];
} Row;

extern UnkStruct_02260f2c data_ov051_0226175c;
extern UnkStruct_02260f2c data_ov051_02261754;
extern UnkStruct_02260f2c data_ov051_0226174c;
extern int data_ov051_02261b84;
extern UnkStruct_02260f2c data_ov051_02261b90[3];
extern int func_0206fc58(void);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov051_022615c0;
extern void *func_020682e0(int);
extern void func_0209e474(void *);
extern int func_020683e4(void *, int, void *, void *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern char data_ov051_02261b68[];
extern void func_020157c8(void *p, int size, int value);
extern int func_02015828(void *p, int value);
extern int func_020a1298(void);
extern int func_020a12d4(void);
extern char func_ov051_022605e8(void *param, int arg);
extern int func_020a12c0(void);
extern int func_020a12ac(void);
extern Row data_ov051_022614cc[];
extern Row2 data_020d19d0[];
extern u8 data_021f43e8;
extern int func_020984e8(void);
extern int func_02099870(int argument0);
extern int func_020950c0(void *argument0);
extern void func_02099834(int t, int a);
extern void func_020997e0(int t, int a);
extern void func_02099808(int t, int a);
extern void func_02099704(int t, u16 *p);
extern void func_ov051_0226122c(char *p, int a);

void func_ov051_02260f2c(UnkStruct_02260f2c_2 *self, int idx)
{
    if ((data_ov051_02261b84 & 1) == 0) {
        data_ov051_02261b90[0] = data_ov051_0226175c;
        data_ov051_02261b90[1] = data_ov051_02261754;
        data_ov051_02261b90[2] = data_ov051_0226174c;
        data_ov051_02261b84 |= 1;
    }
    self->v = data_ov051_02261b90[idx];
}

void func_ov051_02260f04(struct UnkStruct_02260f04 *obj)
{
    unsigned char local;
    local = (unsigned char) func_ov051_022605e8(obj, 0x11);
    func_0206844c(obj->unk_40, (char *) (&local), (*(unsigned int *) &data_ov051_022615c0));
}

void func_ov051_02260ec0(UnkStruct_02260ec0 *param0)
{
    char local[8];

    if (func_0206fc58() != 0) {
        local[0] = 0x29;
        func_0206844c(param0->unk_40, local, data_ov051_022615c0);
    } else {
        local[1] = 9;
        func_0206844c(param0->unk_40, &local[1], data_ov051_022615c0);
    }
}

void func_ov051_02260ea0(void *param0)
{
    unsigned char local;
    void *ptr;

    local = 2;
    ptr = &local;
    func_0206844c((int) (*(void **) ((char *) param0 + 0x40)), (char *) ptr, data_ov051_022615c0);
}

void func_ov051_02260e2c(Param *p)
{
    unsigned char buf[12];
    unsigned int v;
    int b;
    void *r;

    if (p->unk_1E != 0 && p->unk_1E != 2) {
        return;
    }

    r = func_020682e0(0);
    b = 0x19;

    *(unsigned int *) &buf[4] = 0;
    *(unsigned int *) &buf[8] = 0;
    func_0209e474(&buf[4]);

    if (buf[6] >= 12) {
        b = 0x1a;
    }
    buf[0] = b;

    func_020683e4(r, 0, buf, (void *) data_ov051_02261b68);

    v = buf[6];
    if (v >= 12) {
        v -= 12;
    }
    if (v == 0) {
        v = 12;
    }
    if (v == 12) {
        v = 0;
    }

    func_02015fb0(p, v, 1, 2, 0, 0);
}

void func_ov051_02260e08(void *p)
{
    func_020157c8(p, 0x30, 0);
    func_02015828(p, 2);
    func_ov051_02260f2c((UnkStruct_02260f2c_2 *) p, 2);
}

void func_ov051_02260de4(void *p)
{
    func_020157c8(p, 0xf, 0);
    func_02015828(p, 2);
    func_ov051_02260f2c((UnkStruct_02260f2c_2 *) p, 1);
}

void func_ov051_02260dc0(void *p)
{
    func_020157c8(p, 0x10, 0);
    func_02015828(p, 2);
    func_ov051_02260f2c((UnkStruct_02260f2c_2 *) p, 0);
}

void func_ov051_02260d94(UnkStruct_02260d94 *param)
{
    if (func_020a1298()) {
        char local = 0x30;
        func_0206844c(param->unk_40, &local, (*(unsigned int *) &data_ov051_022615c0));
    }
}

void func_ov051_02260d44(struct UnkStruct_02260d44 *param)
{
    char buf[2];
    if (func_020a12d4()) {
        buf[0] = func_ov051_022605e8(param, 21);
        func_0206844c(param->unk_40, &buf[0], (*(unsigned int *) &data_ov051_022615c0));
    } else {
        buf[1] = func_ov051_022605e8(param, 31);
        func_0206844c(param->unk_40, &buf[1], (*(unsigned int *) &data_ov051_022615c0));
    }
}

void func_ov051_02260d1c(UnkStruct_02260d1c *self)
{
    char c = func_ov051_022605e8(self, 0xF);
    func_0206844c((int) self->unk_40, &c, (int) ((*(void * *) &data_ov051_022615c0)));
}

void func_ov051_02260cd8(UnkStruct_02260cd8 *self)
{
    char buf[8];
    if (func_020a12c0()) {
        buf[0] = 0x19;
        func_0206844c(self->unk_40, buf, data_ov051_022615c0);
    } else {
        buf[1] = 0xf;
        func_0206844c(self->unk_40, buf + 1, data_ov051_022615c0);
    }
}

void func_ov051_02260c94(struct UnkStruct_02260c94 *self)
{
    char buf[8];
    if (func_020a12c0()) {
        buf[0] = 0x1a;
        func_0206844c((int) self->unk_40, (char *) buf, (int) ((*(void * *) &data_ov051_022615c0)));
    } else {
        buf[1] = 0x10;
        func_0206844c((int) self->unk_40, (char *) (&buf[1]), (int) ((*(void * *) &data_ov051_022615c0)));
    }
}

void func_ov051_02260c44(int arg0)
{
    char local_8;
    char local_9;

    if (func_020a12ac() != 0) {
        local_8 = (char) func_ov051_022605e8((void *) arg0, 0x25);
        func_0206844c(*(int *) (arg0 + 0x40), &local_8, data_ov051_022615c0);
    } else {
        local_9 = (char) func_ov051_022605e8((void *) arg0, 0x1f);
        func_0206844c(*(int *) (arg0 + 0x40), &local_9, data_ov051_022615c0);
    }
}

void func_ov051_02260c1c(UnkStruct_02260c1c *self)
{
    char c;
    c = func_ov051_022605e8(self, 0x25);
    func_0206844c(self->unk_40, &c, data_ov051_022615c0);
}

void func_ov051_02260b60(UnkStruct_02260b60_2 *self)
{
    u16 hv;
    Row2 *q;
    UnkStruct_02260b60 *p;
    int t;
    int k;
    int code;
    int w;

    if (func_020a12c0() != 0 || func_020a12d4() != 0) {
        t = func_020984e8();

        k = func_020950c0((void *) func_02099870(t));
        if (k == 0) {
            w = data_ov051_022614cc[*(int *) (self->unk_B0 + 0x714)].w[k];
            code = (u8) w;
        } else {
            w = data_ov051_022614cc[*(int *) (self->unk_B0 + 0x714)].w[k];
            code = (u8) (w + 8);
        }
        q = &data_020d19d0[w];
        p = &q->e[k];
        func_02099834(t, code);
        func_020997e0(t, p->b);
        func_02099808(t, q->e[k].a);
        hv = p->c;
        func_02099704(t, &hv);
    }
    func_0206844c(self->unk_40, (char *) (&data_021f43e8), 0);
    func_ov051_0226122c(self->unk_B0, 4);
}
