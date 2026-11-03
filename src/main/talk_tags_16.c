/* talk_tags_16: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206bde0 @ 0x0206bde0, 0x8c bytes, Thumb
 * func_0206bdac @ 0x0206bdac, 0x34 bytes, Thumb
 * func_0206bd74 @ 0x0206bd74, 0x38 bytes, Thumb
 * func_0206bd44 @ 0x0206bd44, 0x30 bytes, Thumb
 * func_0206bd40 @ 0x0206bd40, 0x4 bytes, Thumb
 * func_0206bd2c @ 0x0206bd2c, 0x12 bytes, Thumb
 * func_0206bd24 @ 0x0206bd24, 0x8 bytes, Thumb
 * func_0206bd14 @ 0x0206bd14, 0x10 bytes, Thumb
 * func_0206bca8 @ 0x0206bca8, 0x6c bytes, Thumb
 * func_0206bc98 @ 0x0206bc98, 0x10 bytes, Thumb
 * func_0206bbf4 @ 0x0206bbf4, 0xa4 bytes, Thumb
 * func_0206bbdc @ 0x0206bbdc, 0x16 bytes, Thumb
 * func_0206bba0 @ 0x0206bba0, 0x3a bytes, Thumb
 * func_0206bb9c @ 0x0206bb9c, 0x2 bytes, Thumb
 * func_0206bb74 @ 0x0206bb74, 0x26 bytes, Thumb
 * func_0206bb5c @ 0x0206bb5c, 0x18 bytes, Thumb
 * func_0206ba6c @ 0x0206ba6c, 0xf0 bytes, Thumb
 * func_0206ba64 @ 0x0206ba64, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0206bde0 {
    int unk_00;
    char pad_04[0x20];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    void *unk_38;
    char pad_3C[0x10];
    char unk_4C;
    char unk_4D;
    char unk_4E;
    char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    char unk_60[0x3c];
    char unk_9C[0x3c];
    char unk_D8;
    char unk_D9;
    char pad_DA[2];
    int unk_DC;
    int unk_E0;
};

typedef struct UnkStruct_0206bca8 {
    char pad_00[0x4];
    void *unk_04;
    char pad_08[0x1c];
    unsigned char *unk_24;
    void *unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[0x18];
    char unk_4C;
    char unk_4D;
    char unk_4E;
    char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
    char pad_5C[0x7d];
    char unk_D9;
    char pad_DA[0x2];
    int unk_DC;
    int unk_E0;
} UnkStruct_0206bca8;

typedef struct {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0206bc98;

typedef struct {
    u8 pad_00[0x4];
    u32 unk_04;
    u8 pad_08[0x24 - 0x8];
    u8 *unk_24;
    void *unk_28;
    u32 unk_2C;
    u32 unk_30;
    u8 pad_34[0x50 - 0x34];
    u32 unk_50;
    u8 pad_54[0xd9 - 0x54];
    u8 unk_D9;
    u8 pad_DA[0xdc - 0xda];
    u32 unk_DC;
} UnkStruct_0206bbf4;

typedef struct UnkStruct_0206ba6c {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x14];
    unsigned char unk_4C;
    unsigned char unk_4D;
    unsigned char unk_4E;
    unsigned char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
} UnkStruct_0206ba6c;

extern void *func_020a9484(void *);
extern void func_020a8754(void *);
extern void *func_0206bffc(void *, int, int);
extern unsigned char data_020defe4[];
extern unsigned char data_020e3e68[];
extern void *func_0206bfdc(void *);
extern void *func_020a941c(void *);
extern void func_020edb3c(void *);
extern void func_0206c058(void);
extern void func_0206c2e4(void *, void *);
extern void func_0206c1cc(void *, void *);
extern void func_0206c340(void *ptr);
extern void func_020680d0(void *ptr);
extern int func_02050bdc_unk(int arg);
extern int func_0206c234(void *param1, int param2);
extern void func_02068104(u8 *param1, int param2);
extern void func_020a9318(void *self);
extern void func_020a8764(void *ptr, int);
extern void func_0206b840(void *ptr);
extern int func_0206bef8(void *arg);
extern void func_0206bf08(void *);

int func_0206ba6c(UnkStruct_0206ba6c *s);

struct UnkStruct_0206bde0 *func_0206bde0(struct UnkStruct_0206bde0 *self, int a, int b)
{
    func_020a9484(self);
    self->unk_00 = (int) (unsigned int) data_020e3e68;
    self->unk_00 = (int) (unsigned int) data_020defe4;
    self->unk_24 = a;
    self->unk_28 = b;
    self->unk_2C = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    func_020a8754(&self->unk_38);
    self->unk_4C = 0;
    self->unk_4D = 0;
    self->unk_4E = 0;
    self->unk_4F = 0;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = 0;
    self->unk_5C = 0;
    func_0206bffc(self->unk_60, a, b);
    func_0206bffc(self->unk_9C, a, b);
    self->unk_D8 = 0;
    self->unk_D9 = 0;
    self->unk_DC = 0;
    self->unk_E0 = 0;
    return self;
}

void *func_0206bdac(void *p)
{
    *(void **) p = ((char *) data_020defe4);
    func_0206bfdc((char *) p + 0x9c);
    func_0206bfdc((char *) p + 0x60);
    *(void **) p = ((char *) data_020e3e68);
    func_020a941c(p);
    return p;
}

void *func_0206bd74(void *param)
{
    *(unsigned int *) param = (unsigned int) data_020defe4;
    func_0206bfdc((char *) param + 0x9c);
    func_0206bfdc((char *) param + 0x60);
    *(unsigned int *) param = (unsigned int) data_020e3e68;
    func_020a941c(param);
    func_020edb3c(param);
    return param;
}

void func_0206bd44(void *param)
{
    void *r4 = param;
    *(int *) ((char *) r4 + 0x2c) = 0;
    (void) *(void *volatile *) ((char *) r4 + 0x28);
    func_0206c058();
    func_0206c2e4(*(void **) ((char *) r4 + 0x28), *(void **) ((char *) r4 + 0x5c));
    func_0206c1cc(*(void **) ((char *) r4 + 0x28), *(void **) ((char *) r4 + 4));
    *(char *) ((char *) r4 + 0xd9) = 0;
    *(int *) ((char *) r4 + 0xe0) = 0;
}

void func_0206bd40(int *p0, int p1)
{
    p0[13] = p1;
}

void func_0206bd2c(unsigned char *p)
{
    if (p[0x4f] == 0) {
        p[0x4c] = 1;
    }
}

void func_0206bd24(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (76))) + (0)) = 0;
}

void func_0206bd14(void *r0)
{
    unsigned int r2 = 0;
    *(unsigned int *) ((char *) r0 + 0x5c) = r2;
    {
        unsigned int r1 = *(unsigned int *) ((char *) r0 + 0x24);
        *(unsigned int *) ((char *) r1 + 0x1a54) = r2;
    }
}

void func_0206bca8(UnkStruct_0206bca8 *p)
{
    p->unk_30 = 1;
    p->unk_2C = 0;
    p->unk_4C = 0;
    p->unk_4D = 0;
    p->unk_4E = 0;
    p->unk_4F = 0;
    p->unk_50 = 0;
    p->unk_54 = 0;
    p->unk_58 = 0;
    func_0206c340(p->unk_28);
    func_0206c1cc(p->unk_28, p->unk_04);
    func_020680d0(p->unk_24);
    p->unk_D9 = 0;
    p->unk_DC = 0;
    p->unk_E0 = 0;
    *(p->unk_24 + 0x1a49) = 0;
    *(p->unk_24 + 0x1a4a) = 0;
}

void func_0206bc98(UnkStruct_0206bc98 *self)
{
    self->unk_30 = 3;
    (void) *(void *volatile *) &self->unk_28;
    func_0206c058();
}

void func_0206bbf4(UnkStruct_0206bbf4 *self, int arg)
{
    int is10;
    int is3000;

    if (self->unk_D9 != 0) {
        arg = func_02050bdc_unk(arg);
        self->unk_D9 = 0;
    }

    is10 = (arg == 10) ? 1 : 0;
    is3000 = (arg == 0x3000) ? 1 : 0;

    func_0206c234(self->unk_28, arg);

    if (is10) {
        func_0206c1cc(self->unk_28, (void *) self->unk_04);
        self->unk_2C++;
        if (self->unk_2C >= 3) {
            self->unk_30 = 2;
        }
    }

    func_02068104(self->unk_24, arg);
    self->unk_24[0x1a4a] = 0;

    if (is3000 == 0 && is10 == 0) {
        self->unk_50++;
    }

    if (self->unk_04 == self->unk_DC) {
        self->unk_DC = 0;
        func_020a9318(self);
    }
}

void func_0206bbdc(void *arg, int argument1)
{
    void *r4 = arg;
    func_020a8764((char *) r4 + 0x38, (int) argument1);
    func_0206b840(r4);
}

int func_0206bba0(void *r0)
{
    int r4 = 1;
    int r1 = *(int *) ((char *) r0 + 0x30);
    if (r1 == 2 || r1 == 5) {
        r4 = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
        *(int *) ((char *) r0 + 0x58) = 0;
    } else if (r1 == 4) {
        r4 = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
    } else if (r1 == 1) {
        if (func_0206ba6c((UnkStruct_0206ba6c *) r0) == 0) {
            r4 = 0;
        }
    }
    return r4;
}

void func_0206bb9c(void *object, int code, const void *message) {}

int func_0206bb74(void *p)
{
    if (func_0206bef8((char *) p + 0x60) && func_0206bef8((char *) p + 0x9c)) {
        return 1;
    }
    return 0;
}

void func_0206bb5c(void *arg0)
{
    void *ptr;
    ptr = arg0;
    func_0206bf08((void *) ((unsigned int) ptr + 0x60));
    func_0206bf08((void *) ((unsigned int) ptr + 0x9c));
}

int func_0206ba6c(UnkStruct_0206ba6c *s)
{
    int res = 1;
    unsigned flag = res;
    unsigned cond;
    int r4;

    if (s->unk_34 != 1 && s->unk_4E == 0) {
        flag = 0;
    }

    if (s->unk_4D != 0) {
        res = 0;
        s->unk_4D = 0;
        goto end;
    }

    if (flag != 0) {
        s->unk_50 = 0;
        s->unk_54 = 0;
        s->unk_58 = 0;
        while (func_0206bb74((void *) s) == 0) {
            func_0206bb5c((void *) s);
        }
    } else {
        if (s->unk_34 != 2 && s->unk_4F == 0 && s->unk_4C != 0) {
            cond = 1;
        } else {
            cond = 0;
        }

        if (cond != 0) {
            s->unk_58 = 0;
        }

        if (s->unk_58 > 0) {
            s->unk_58 -= 0x1800;
            res = 0;
            goto end;
        }

        if (s->unk_54 == 0) {
            r4 = 1;
        } else {
            r4 = 2;
        }

        if (cond != 0) {
            r4 = 3;
        }

        if (s->unk_50 >= r4) {
            s->unk_50 = 0;
            s->unk_54++;
            if (s->unk_54 >= 2) {
                s->unk_54 = 0;
            }
            res = 0;
            goto end;
        } else {
            while (func_0206bb74((void *) s) == 0) {
                func_0206bb5c((void *) s);
                s->unk_50++;
                if (s->unk_50 >= r4) {
                    s->unk_50 = 0;
                    s->unk_54++;
                    if (s->unk_54 >= 2) {
                        s->unk_54 = 0;
                    }
                    res = 0;
                    goto end;
                }
            }
        }
    }

end:
    return res;
}

void func_0206ba64(int p0)
{
    *(int *) ((char *) (((int) (p0) + (224))) + (0)) = 0;
}
