/* nook_clerk_talk_2: 15 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_022614c8 @ 0x022614c8, 0x98 bytes, Thumb
 * func_ov050_02261494 @ 0x02261494, 0x34 bytes, Thumb
 * func_ov050_02261480 @ 0x02261480, 0x14 bytes, Thumb
 * func_ov050_022613d8 @ 0x022613d8, 0xa8 bytes, Thumb
 * func_ov050_02261390 @ 0x02261390, 0x48 bytes, Thumb
 * func_ov050_022612f4 @ 0x022612f4, 0x9c bytes, Thumb
 * func_ov050_02261200 @ 0x02261200, 0xf4 bytes, Thumb
 * func_ov050_02261174 @ 0x02261174, 0x8c bytes, Thumb
 * func_ov050_02261138 @ 0x02261138, 0x3c bytes, Thumb
 * func_ov050_022610b0 @ 0x022610b0, 0x86 bytes, Thumb
 * func_ov050_02261094 @ 0x02261094, 0x1c bytes, Thumb
 * func_ov050_02261078 @ 0x02261078, 0x1c bytes, Thumb
 * func_ov050_0226105c @ 0x0226105c, 0x1c bytes, Thumb
 * func_ov050_02261040 @ 0x02261040, 0x1c bytes, Thumb
 * func_ov050_02260f28 @ 0x02260f28, 0x118 bytes, Thumb
 */

#include "types.h"

#define GroundPredicate ((int (*)(unsigned short *, int)) func_ov050_022637c0)

struct UnkStruct_022614c8 {
    char pad_00[0xd0];
    int unk_D0;
};

typedef struct {
    unsigned char pad_00[0xD0];
    unsigned int unk_D0;
} UnkStruct_02261494;

typedef struct UnkStruct_022613d8 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
    char pad_C8[0xd0 - 0xc8];
    int unk_D0;
} UnkStruct_022613d8;

struct UnkStruct_02261390 {
    char pad_00[0xb4];
    unsigned int unk_B4;
    char pad_B8[12];
    unsigned int unk_C4;
    char pad_C8[8];
    unsigned int unk_D0;
};

typedef struct {
    u8 pad_00[0xb4];
    u8 *data;
} UnkStruct_022612f4;

typedef struct UnkStruct_02261200 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
    char pad_C8[0xd0 - 0xc8];
    int unk_D0;
} UnkStruct_02261200;

struct UnkStruct_02261174 {
    char pad_00[0xb4];
    unsigned char *base;
    char pad_B8[0xc];
    int other;
    char pad_C8[0x8];
    int value;
};

typedef struct {
    char pad_00[0x1E];
    unsigned char unk_1E;
    char pad_1F[0x95];
    void *unk_B4;
    char pad_B8[8];
    void *unk_C0;
    void *unk_C4;
    char pad_C8[8];
    int unk_D0;
} UnkStruct_022610b0;

struct UnkStruct_02261078 {
    char pad_00[0xd0];
    int unk_D0;
};

typedef struct {
    char pad_00[0xd0];
    int unk_D0;
} UnkStruct_0226105c;

typedef struct UnkStruct_02260f28 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    unsigned int unk_40;
    char pad_44[0xb4 - 0x44];
    void *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02260f28;

extern int func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_020ada14(void);
extern int func_0209ded0(void);
extern int func_020874c4(const void *p);
extern void func_02015fb0(void *a, int b, int c, int d, int e, int f);
extern unsigned char data_021f3b0c;
extern unsigned short func_ov050_022637c0(unsigned short *value, int event);
extern void func_020157d4(void *a, int (*callback)(unsigned short *, int), unsigned char c, unsigned char d);
extern int func_02015828(void *a, int b);
extern void func_ov050_02263b38(void *a, int b);
extern void func_0206fa8c(int a);
extern int func_0201b43c(char *a, int b);
extern void func_0201b420(char *a, int b);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020ad944(u16 *p);
extern int func_02099fe8(void);
extern void func_ov050_02260dd4(struct UnkStruct_02261390 *);
extern int func_02034aa8(int);
extern int func_02034a74(int);
extern int func_0203aeac(void);
extern int func_ov004_0224730c(void);
extern int func_ov004_022472ec(void);
extern int func_02034b80(u16 *p, int a, int b, int c);
extern void *func_02034b04(u16 *p, int a, int b, int c);
extern int func_02099870(int argument0);
extern int func_0209871c(void *a, int b);
extern int func_020b65c4(void);
extern void func_020ada48(int a, int b, int c, int d);
extern unsigned char data_021dc7bc[];
extern void func_0209a050(void *object);
extern int func_02015330(int *p, short *s, int a, int b, int c);
extern int func_0201b3c0(void *a, void *b, void *c);
extern void func_0201b3a4(void *a, void *b);
extern void func_020adb24(void *a);
extern void func_ov050_022618d0(void *, int, int);
extern int func_020160b4(UnkStruct_02260f28 *self);
extern int func_020ab504(void *argument0);
extern void func_ov050_02263640(UnkStruct_02260f28 *self, int arg);
extern int func_ov050_02260510(void *p);
extern int func_0202ea40(void *p, char *buffer, int count);
extern void func_0202ea28(void *p, char *buffer);
extern void func_0206844c(unsigned int val, char *str, void *data);
extern unsigned char data_ov050_02265824[];

void func_ov050_022614c8(struct UnkStruct_022614c8 *obj, int val)
{
    func_020984e8();
    switch (val) {
        case 0:
            obj->unk_D0 = 7;
            break;
        case 1:
            if (func_0202e9fc() == 0) {
                obj->unk_D0 = 0x59;
            } else if (func_020ada14() != 0) {
                obj->unk_D0 = 0x18;
            } else {
                obj->unk_D0 = 0x17;
            }
            break;
        case 2:
            if (func_0209ded0() != 0) {
                int r = func_020874c4(&data_021f3b0c);
                func_02015fb0(obj, r, 1, 3, 0, 0);
                obj->unk_D0 = 0x16;
            } else {
                obj->unk_D0 = 0xd;
            }
            break;
        case 3:
            obj->unk_D0 = 0x15;
            break;
    }
}

void func_ov050_02261494(UnkStruct_02261494 *self, int flag)
{
    if (flag == 0) {
        func_020157d4(self, GroundPredicate, 13, 0);
        func_02015828(self, 0);
        func_ov050_02263b38(self, 2);
    } else {
        self->unk_D0 = 15;
    }
}

void func_ov050_02261480(int a, int b)
{
    if (b != 0) {
        func_0206fa8c(0);
    }
}

void func_ov050_022613d8(UnkStruct_022613d8 *self, int mode)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;

    if (mode == 0) {
        if (func_0201b43c(self->unk_B4, self->unk_C4) != 0) {
            func_0201b420(self->unk_B4, self->unk_C4);
            self->unk_D0 = 0x1c;
            p = (u16 *) (self->unk_B4 + 0x732);
            if (func_0204bcdc(p) != 0) {
                tmp = 0xfff1;
                r = func_0204bc64(p);
                ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
            } else {
                ok = (*p == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                func_020ad944((u16 *) (self->unk_B4 + 0x732));
            }
        } else {
            self->unk_D0 = 0x1d;
        }
    } else {
        self->unk_D0 = 0x1b;
    }
}

void func_ov050_02261390(struct UnkStruct_02261390 *p, int flag)
{
    if (flag != 0) {
        return;
    }
    if (func_02099fe8() < 0) {
        p->unk_D0 = 0x20;
        return;
    }
    if (func_0201b43c((char *) p->unk_B4, p->unk_C4) == 0) {
        p->unk_D0 = 0x21;
        return;
    }
    p->unk_D0 = 0x22;
    func_ov050_02260dd4(p);
}

void func_ov050_022612f4(UnkStruct_022612f4 *self, int arg1)
{
    u16 *p;
    int r;

    p = (u16 *) (self->data + 0x732);

    if (func_0204bcdc((u16 *) p)) {
        u16 key = 0xfff1;
        if (func_0204bc64((u16 *) p) == func_0204bc64((u16 *) (&key))) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (*p == 0xfff1) {
            r = 1;
        } else {
            r = 0;
        }
    }

    if (!r) {
        int inRange = 0;
        u16 v;

        v = *(u16 *) (self->data + 0x732);
        if (v >= 0x1100 && v <= 0x1143) {
            inRange = 1;
        }

        if (inRange) {
            func_02034aa8(1);
        } else {
            func_02034a74(1);
        }

        func_0203aeac();
    }

    func_ov050_02261390((struct UnkStruct_02261390 *) self, arg1);
}

void func_ov050_02261200(UnkStruct_02261200 *self, int mode)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;
    unsigned int in1;

    if (mode == 0) {
        if (func_02099fe8() < 0) {
            self->unk_D0 = 0x20;
        } else if (func_0201b43c(self->unk_B4, self->unk_C4) == 0) {
            self->unk_D0 = 0x21;
        } else {
            self->unk_D0 = 0x22;
            func_ov050_02260dd4((struct UnkStruct_02261390 *) self);
        }
    } else if (mode == 1) {
        p = (u16 *) (self->unk_B4 + 0x732);
        if (func_0204bcdc(p) != 0) {
            tmp = 0xfff1;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
        } else {
            ok = (*p == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            in1 = 0;
            if (*(u16 *) (self->unk_B4 + 0x732) >= 0x1100 && *(u16 *) (self->unk_B4 + 0x732) <= 0x1143) {
                in1 = 1;
            }
            if (in1 != 0) {
                func_ov004_0224730c();
                func_02034b80((u16 *) (self->unk_B4 + 0x732), 0, 1, 1);
            } else {
                func_ov004_022472ec();
                func_02034b04((u16 *) (self->unk_B4 + 0x732), 0, 1, 1);
            }
        }
    }
}

void func_ov050_02261174(struct UnkStruct_02261174 *self, int cond)
{
    if (cond == 0) {
        if (func_0201b43c((char *) self->base, self->other) == 0) {
            self->value = 0x21;
        } else {
            int v, rv;
            unsigned char *base;
            self->value = 0x22;
            self->base[0x73c] = 1;
            func_0201b420((char *) self->base, self->other);

            v = func_02099870((int) func_020984e8());
            func_0209871c((void *) data_021dc7bc, v);
            base = self->base;
            rv = func_020b65c4();
            func_020ada48(*(int *) (base + 0x734), *(int *) (base + 0x738), self->other, rv);
        }
    }
}

void func_ov050_02261138(int *p, int flag)
{
    if (flag == 0) {
        int object = p[51];
        if (object >= 0) {
            int a;
            short s;
            func_0209a050((void *) object);
            s = 0x36fc;
            a = 0;
            func_02015330(p, &s, a, 5, a);
        }
        p[52] = 55;
    }
}

void func_ov050_022610b0(UnkStruct_022610b0 *s, int flag)
{
    if (flag == 0) {
        int ret;
        ret = func_0201b3c0(s->unk_B4, s->unk_C4, s->unk_C0);
        switch (ret) {
            case 0:
                func_0201b3a4(s->unk_B4, s->unk_C4);
                func_020adb24(s->unk_C4);
                s->unk_D0 = 0x12;
                break;
            case 1:
                func_020adb24(s->unk_C4);
                s->unk_D0 = 0x13;
                break;
            case 2:
                s->unk_D0 = 0x5D;
                func_0206fa8c(0);
                break;
        }
    } else {
        if (s->unk_1E != 0x40) {
            func_0206fa8c(0);
        } else {
            func_0206fa8c(1);
        }
    }
}

void func_ov050_02261094(void *p, int a)
{
    if (a != 4) {
        func_ov050_022618d0(p, 0, a);
        *(int *) ((char *) p + 0xD0) = 0x48;
    }
}

void func_ov050_02261078(struct UnkStruct_02261078 *self, int param2)
{
    if (param2 != 4) {
        func_ov050_022618d0(self, 1, param2);
        self->unk_D0 = 0x48;
    }
}

void func_ov050_0226105c(UnkStruct_0226105c *self, int value)
{
    if (value != 4) {
        func_ov050_022618d0((void *) self, 2, value);
        self->unk_D0 = 0x48;
    }
}

void func_ov050_02261040(int *p, int x)
{
    if (x == 4) {
        return;
    }
    func_ov050_022618d0((void *) p, 3, x);
    p[0x34] = 0x48;
}

void func_ov050_02260f28(UnkStruct_02260f28 *self)
{
    int r5;
    char buffer[2];
    int *gp;

    r5 = func_020ab504((void *) func_020160b4(self));
    func_020984e8();
    gp = ((int *) &data_021f3b0c);

    if ((int) self->unk_1E > 0x14) {
        return;
    }

    self->unk_D0 = 0xff;

    if (r5 != 3) {
        func_ov050_02263640(self, 5);
    }

    switch (r5) {
        case 0:
            self->unk_D0 = 7;
            break;
        case 1:
            if (func_0202e9fc() == 0) {
                self->unk_D0 = 0x59;
            } else if (func_020ada14() != 0) {
                self->unk_D0 = 0x18;
            } else {
                self->unk_D0 = 0x17;
            }
            break;
        case 2:
            if (func_0209ded0()) {
                int ret = func_020874c4((const void *) gp);
                func_02015fb0((void *) self, ret, 1, 3, 0, 0);
                self->unk_D0 = 0x16;
            } else {
                self->unk_D0 = 0x0d;
            }
            break;
        case 3:
            if (func_ov050_02260510(self->unk_B4)) {
                if (func_0202ea40(self->unk_B4, buffer, 3)) {
                    func_0202ea28(self->unk_B4, buffer);
                }
            }
            break;
        case 4:
            self->unk_D0 = 0x15;
            break;
    }

    if (self->unk_D0 != 0xff) {
        buffer[1] = (char) self->unk_D0;
        func_0206844c(self->unk_40, &buffer[1], data_ov050_02265824);
    }
}
