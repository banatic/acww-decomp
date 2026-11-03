/* owl_donation: 18 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_022610a4 @ 0x022610a4, 0x28 bytes, Thumb
 * func_ov047_0226107c @ 0x0226107c, 0x28 bytes, Thumb
 * func_ov047_02261068 @ 0x02261068, 0x14 bytes, Thumb
 * func_ov047_02261054 @ 0x02261054, 0x14 bytes, Thumb
 * func_ov047_0226102c @ 0x0226102c, 0x28 bytes, Thumb
 * func_ov047_0226100c @ 0x0226100c, 0x20 bytes, Thumb
 * func_ov047_02260f24 @ 0x02260f24, 0xe8 bytes, Thumb
 * func_ov047_02260ec0 @ 0x02260ec0, 0x64 bytes, Thumb
 * func_ov047_02260e58 @ 0x02260e58, 0x68 bytes, Thumb
 * func_ov047_02260e44 @ 0x02260e44, 0x14 bytes, Thumb
 * func_ov047_02260e18 @ 0x02260e18, 0x2c bytes, Thumb
 * func_ov047_02260df0 @ 0x02260df0, 0x28 bytes, Thumb
 * func_ov047_02260dbc @ 0x02260dbc, 0x34 bytes, Thumb
 * func_ov047_02260d28 @ 0x02260d28, 0x94 bytes, Thumb
 * func_ov047_02260c9c @ 0x02260c9c, 0x8c bytes, Thumb
 * func_ov047_02260be0 @ 0x02260be0, 0xbc bytes, Thumb
 * func_ov047_02260bc0 @ 0x02260bc0, 0x20 bytes, Thumb
 * func_ov047_02260b9c @ 0x02260b9c, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xc8];
    int unk_C8;
    unsigned char pad_CC[2];
    unsigned short unk_CE;
    int unk_D0;
} UnkStruct_02260f24;

typedef struct {
    unsigned char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char pad_CD[3];
    int unk_D0;
} UnkStruct_02260e18;

typedef struct {
    char pad_00[0xD0];
    int unk_D0;
} UnkStruct_02260dbc;

struct UnkStruct_02260c9c {
    u8 pad_00[0xce];
    u16 unk_CE;
    u32 unk_D0;
};

typedef struct UnkStruct_02260be0 {
    char pad_00[0xce];
    u16 unk_CE;
    int unk_D0;
} UnkStruct_02260be0;

extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *p, int arg2);
extern void func_ov047_02261f84(void *p, int arg2);
extern int func_ov047_02261ea4(void *argument0, int argument1);
extern unsigned short func_ov047_02261c00(void *argument0, int argument1);
extern int func_02014f60(int argument0);
extern int func_0209f150(void *p, int n);
extern int data_021dc7a8;
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_02063414(void *a, int b, int c, void *d, int e, int f, int g, int h, int i, int j);
extern void func_0209a088(void *a, int b, int _x);
extern void func_02015de4(void *a, void *b, int c, int d);
extern int func_020644cc(int a);
extern int data_020ccf94;
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int func_0202e9fc(void);
extern int func_02071298(const char *, const char *);
extern unsigned char data_021f38f8[];
extern int func_02015094(void *);
extern void func_ov047_02261618(void *);
extern int func_02070fa0(void *ptr);
extern int func_02070edc(void *ptr);
extern void func_020157c8(void *p, int a, int b);

void func_ov047_0226102c(int *p);

void func_ov047_022610a4(void *p)
{
    func_020157d4(p, (unsigned int) func_ov047_02261ea4, 13, 1);
    func_02015828(p, 0);
    func_ov047_02261f84(p, 0);
}

void func_ov047_0226107c(void *param)
{
    func_020157d4(param, (unsigned int) func_ov047_02261c00, 13, 1);
    func_02015828(param, 0);
    func_ov047_02261f84(param, 1);
}

void func_ov047_02261068(void *arg)
{
    func_02014f60((int) arg);
    func_ov047_0226102c((int *) arg);
}

void func_ov047_02261054(void *p)
{
    func_02014f60((int) p);
    *(unsigned int *) ((char *) p + 0xd0) = 0x6b;
}

void func_ov047_0226102c(int *p)
{
    if (func_0209f150(&data_021dc7a8, 12)) {
        p[52] = 0x46;
    } else {
        p[52] = 0x45;
    }
}

void func_ov047_0226100c(void *self)
{
    unsigned short v = *(unsigned short *) ((char *) self + 0xCE);
    if (v != 0xFFF1) {
        func_02014f60((int) self);
    }
}

void func_ov047_02260f24(UnkStruct_02260f24 *self)
{
    unsigned char buf[12];
    unsigned int cond;
    int a, b;

    if (func_0204bcdc(&self->unk_CE) != 0) {
        *(unsigned short *) (buf + 4) = 0xfff1;
        a = func_0204bc64(&self->unk_CE);
        b = func_0204bc64(buf + 4);
        if (a == b) {
            cond = 1;
        } else {
            cond = 0;
        }
    } else {
        if (self->unk_CE == 0xfff1) {
            cond = 1;
        } else {
            cond = 0;
        }
    }

    if (cond != 0) {
        goto end;
    }

    {
        int t = func_020984e8();
        func_02098ff8(t, 0x35);

        func_02063414(buf + 2, 0x450c, 0x34, 0, 0, 0, 1, 10, 0, 1);
        self->unk_CE = *(unsigned short *) (buf + 2);

        if (self->unk_C8 >= 0) {
            func_0209a088(&self->unk_CE, 0, self->unk_C8);
        }

        func_02015de4(self, &self->unk_CE, 0, 7);
        func_02063414(buf, 0x450c, 0x34, &self->unk_CE, 1, 0, 1, 10, 0, 1);
        func_02015de4(self, buf, 1, 7);
    }

end:
    self->unk_D0 = (unsigned char) (func_020644cc(3) + 0x1a);
}

void func_ov047_02260ec0(char *p)
{
    if (*(unsigned char *) (p + 0xcc) == 0) {
        if (func_02073d90(data_020ccf94) == 0 && *func_0209d358(0, 0x4a) == 0 && func_0202e9fc() != 0 &&
            func_02071298((const char *) data_021f38f8, p + 0xce) == 0) {
            *(int *) (p + 0xd0) = 0x69;
        } else {
            *(int *) (p + 0xd0) = 0x6a;
        }
    } else {
        *(int *) (p + 0xd0) = 0x1d;
    }
}

void func_ov047_02260e58(char *p)
{
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        func_02014f60((int) p);
        *(int *) (p + 0xd0) = 0x20;
        return;
    }
    if (func_0202e9fc() != 0 && func_02071298((const char *) data_021f38f8, p + 0xce) == 0) {
        *(int *) (p + 0xd0) = 0x1e;
        return;
    }
    func_02014f60((int) p);
    *(int *) (p + 0xd0) = 0x20;
}

void func_ov047_02260e44(void *arg)
{
    func_02014f60((int) arg);
    *(unsigned int *) ((char *) arg + 0xd0) = 0x20;
}

void func_ov047_02260e18(UnkStruct_02260e18 *self)
{
    func_02015094(self);
    func_ov047_02261618(self);

    if (self->unk_CC == 0) {
        self->unk_D0 = 0x27;
    } else {
        self->unk_D0 = 0x20;
    }
}

void func_ov047_02260df0(void *self)
{
    if (func_02070fa0(((int *) data_021f38f8)) != 0) {
        *(int *) ((char *) self + 0xd0) = 0x2a;
    } else {
        *(int *) ((char *) self + 0xd0) = 0x2b;
    }
}

void func_ov047_02260dbc(UnkStruct_02260dbc *p)
{
    func_ov047_02261618(p);
    if (func_02070edc(((int *) data_021f38f8))) {
        p->unk_D0 = 49;
    } else {
        p->unk_D0 = 39;
    }
    func_02015094(p);
}

void func_ov047_02260d28(unsigned char *p)
{
    unsigned char *ptr;
    unsigned char *ptr3;
    unsigned int *ptr2;
    if (p[0x1e] == 0x32) {
        int cond;
        unsigned short local;
        unsigned short value;
        int inRange;
        int delta;
        if (func_0204bcdc(p + 0xce)) {
            int call1;
            int call2;
            local = 0xfff1;
            call1 = func_0204bc64(p + (0xce & 0xFFFF));
            call2 = func_0204bc64(&local);
            cond = (call1 == call2) ? (1) : (0);
        } else {
            cond = ((*((unsigned short *) (p + 0xce))) == 0xfff1) ? (1) : (0);
        }
        if (cond) {
            return;
        }
        ptr = p + 0xce;
        inRange = 0;
        value = *((unsigned short *) ptr);
        if ((value >= 0x12b0) && (value <= 0x12e7)) {
            inRange = 1;
        }
        ptr3 = p;
        if (inRange) {
            delta = value - 0x12b0;
        } else {
            cond = ((*((unsigned short *) (p + 0xce))) == 0xfff1) ? (1) : (0);
            delta = -1;
        }
        delta = delta + 0x6e;
        ptr2 = (unsigned int *) (ptr3 + 0xd0);
        *ptr2 = (unsigned char) delta;
    }
}

void func_ov047_02260c9c(struct UnkStruct_02260c9c *self)
{
    u16 tmp;
    unsigned int first_match;
    unsigned int in_range;
    u16 v;
    int adj;

    if (func_0204bcdc(&self->unk_CE) != 0) {
        tmp = 0xfff1;
        first_match = (func_0204bc64(&self->unk_CE) == func_0204bc64(&tmp)) ? 1u : 0u;
    } else {
        first_match = (self->unk_CE == 0xfff1) ? 1u : 0u;
    }
    if (first_match != 0) {
        return;
    }

    in_range = 0;
    v = self->unk_CE;
    if (v >= 0x12e8 && v <= 0x131f) {
        in_range = 1;
    }
    if (in_range) {
        adj = v - 0x12e8;
    } else {
        adj = -1;
    }
    self->unk_D0 = (u8) (adj + 0xaa);
}

void func_ov047_02260be0(UnkStruct_02260be0 *self)
{
    u16 tmp;
    int r;
    unsigned int ok;
    unsigned int hit;

    if (func_0204bcdc((void *) (&self->unk_CE)) != 0) {
        tmp = 0xfff1;
        r = func_0204bc64((void *) (&self->unk_CE));
        ok = (r == func_0204bc64((void *) (&tmp))) ? 1 : 0;
    } else {
        ok = (self->unk_CE == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        hit = 0;
        if (self->unk_CE >= 0x450c && self->unk_CE <= 0x45db) {
            hit = 1;
        }
        if (hit != 0) {
            self->unk_D0 = 0x3a;
        } else if (self->unk_CE >= 0x12b0 && self->unk_CE <= 0x12e7) {
            self->unk_D0 = 0x3b;
        } else if (self->unk_CE >= 0x12e8 && self->unk_CE <= 0x131f) {
            self->unk_D0 = 0x3c;
        } else {
            self->unk_D0 = 0x3d;
        }
    }
}

void func_ov047_02260bc0(void *param)
{
    unsigned short *p;
    int *q;

    func_02014f60((int) param);
    p = (unsigned short *) ((char *) param + 0xce);
    *p = 0xfff1;
    q = (int *) ((char *) param + 0xd0);
    *q = 0x23;
}

void func_ov047_02260b9c(void *p)
{
    func_020157c8(p, 0x41, 0);
    func_02015828(p, 2);
    func_ov047_02261f84(p, 3);
}
