/* talk_windows: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aa170 @ 0x020aa170, 0xe bytes, Thumb
 * func_020aa164 @ 0x020aa164, 0xc bytes, Thumb
 * func_020aa154 @ 0x020aa154, 0x10 bytes, Thumb
 * func_020aa13c @ 0x020aa13c, 0x18 bytes, Thumb
 * func_020aa09c @ 0x020aa09c, 0xa0 bytes, Thumb
 * func_020a9fac @ 0x020a9fac, 0xf0 bytes, Thumb
 * func_020a9fa4 @ 0x020a9fa4, 0x6 bytes, Thumb
 * func_020a9ebc @ 0x020a9ebc, 0xe8 bytes, Thumb
 * func_020a9e8c @ 0x020a9e8c, 0x30 bytes, Thumb
 * func_020a9e04 @ 0x020a9e04, 0x88 bytes, Thumb
 * func_020a9ddc @ 0x020a9ddc, 0x28 bytes, Thumb
 * func_020a9dc8 @ 0x020a9dc8, 0x14 bytes, Thumb
 * func_020a9db0 @ 0x020a9db0, 0x16 bytes, Thumb
 * func_020a9d88 @ 0x020a9d88, 0x28 bytes, Thumb
 * func_020a9d70 @ 0x020a9d70, 0x18 bytes, Thumb
 * func_020a9d38 @ 0x020a9d38, 0x38 bytes, Thumb
 * func_020a9d24 @ 0x020a9d24, 0x14 bytes, Thumb
 * func_020a9d14 @ 0x020a9d14, 0xe bytes, Thumb
 * func_020a9cf8 @ 0x020a9cf8, 0x1c bytes, Thumb
 * func_020a9ce0 @ 0x020a9ce0, 0x16 bytes, Thumb
 */

typedef struct UnkStruct_020aa09c {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char sub[0x148];
    unsigned char sub2[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
} UnkStruct_020aa09c;

typedef struct UnkStruct_020a9fac {
    unsigned char pad_00[0xc];
    unsigned char pad_0C[0x148];
    unsigned char pad_154[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
} UnkStruct_020a9fac;

typedef struct {
    unsigned char pad_00[8];
    unsigned long unk_08;
} UnkStruct_020a9fa4;

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x188];
    int unk_194;
    char unk_198;
} UnkStruct_020a9e8c;

struct UnkStruct_020a9e04 {
    char pad_00[0xc];
    char sub[0x148];
    char sub154[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
    char unk_198;
};

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned char unk_0C;
    unsigned char pad_0D[0x147];
    unsigned char unk_154;
} SELF;

typedef struct {
    char data[0xC4];
} SubA;

typedef struct {
    char data[0x19C];
} SubB;

struct UnkStruct_020a9d88 {
    int unk_00;
    SubA a;
    SubB b;
    char unk_264;
};

typedef int (*FuncPtr)(void *);

typedef struct Vtbl Vtbl;

struct Vtbl {
    FuncPtr fn0;
    FuncPtr fn1;
    FuncPtr fn2;
    FuncPtr fn3;
    FuncPtr fn4;
};

typedef struct UnkStruct_020a9d38 UnkStruct_020a9d38;

struct UnkStruct_020a9d38 {
    Vtbl *vtable;
};

typedef struct {
    UnkStruct_020a9d38 *ptr;
    unsigned char pad_04[0x260];
    unsigned char flag;
} UnkStruct_020a9d38_2;

typedef struct UnkStruct_020a9cf8 UnkStruct_020a9cf8;

typedef struct Vtable Vtable;

struct Vtable {
    int (*unk_00)();
    int (*unk_04)();
    int (*unk_08)();
    int (*unk_0C)();
    int (*unk_10)();
    int (*unk_14)(UnkStruct_020a9cf8 *);
};

struct UnkStruct_020a9cf8 {
    Vtable *vtable;
};

typedef void (*Handler)(void *);

extern void func_020ac3e0(unsigned int *);
extern int func_020ac8c8(unsigned char *s);
extern void func_020aae40(unsigned char *s);
extern void func_020ac444(unsigned char *s);
extern void func_020ac424(unsigned char *s);
extern void func_020ac3ec(unsigned char *s);
extern void func_020ac8a8(unsigned char *s);
extern int func_0209d368(int a, int b);
extern void func_020ac384(unsigned char *s);
extern void func_0200467c(int cmd);
extern void func_020ac39c(void *a, int b, int c);
extern void func_020abdc8(void *a);
extern int func_020aad3c(void *a);
extern void func_020abd68(void *a, int b, int c);
extern void func_020aae38(void *a);
extern void func_020aad9c(char *);
extern void func_020abd5c(char *, int);
extern int func_020aae88(char *);
extern int func_020aae78(char *);
extern int func_020abcc0(char *);
extern int func_020aad8c(char *);
extern int func_020abccc(char *);
extern void func_020abcb4(char *);
extern int func_020aad5c(char *);
extern void func_020abca8(char *);
extern void func_020abc9c(char *);
extern int func_020aad7c(char *);
extern int func_020abce4(char *);
extern void func_020abc90(char *);
extern void func_020abdc0(char *);
extern void func_020aae30(char *);
extern void func_020abc84(char *);
extern void func_020aae14(void *);
extern int func_020aae84(unsigned char *);
extern void func_020ac46c(unsigned char *, int);
extern void func_020ac4ec(unsigned char *);
extern void func_020aa7e8(void *, void *);
extern void func_020aa2e4(void *, int);
extern void *func_020aa79c(void *);
extern void *func_020aa28c(void *);
extern void *func_020aa25c(void *p);
extern void *func_020aa770(void *p);
extern void func_020aa7f4(void *);

void func_020aa09c(UnkStruct_020aa09c *p);
void func_020a9fa4(UnkStruct_020a9fa4 *p);
void func_020a9e8c(UnkStruct_020a9e8c *object);
void func_020a9ddc(SELF *self);

int func_020aa170(void *arg0)
{
    if (*(int *) ((char *) arg0 + 8) == 0) {
        return 1;
    }
    return 0;
}

unsigned char func_020aa164(unsigned char *r0)
{
    return r0[0x198];
}

void func_020aa154(unsigned int *p)
{
    p[2] = 0;
    func_020ac3e0(p + 3);
}

void func_020aa13c(unsigned char *r0)
{
    if (r0[4] != 0) {
        r0[4] = 0;
        func_020aa09c((UnkStruct_020aa09c *) r0);
    }
}

void func_020aa09c(UnkStruct_020aa09c *p)
{
    p->unk_08 = 1;
    func_020ac8c8(p->sub);
    func_020aae40(p->sub2);
    func_020a9ddc((SELF *) p);
    func_020ac444(p->sub);
    func_020ac424(p->sub);
    func_020ac3ec(p->sub);
    func_020ac8a8(p->sub);
    p->unk_194 = func_0209d368(100, 2) + 3;
    p->unk_18C = func_0209d368(100, 4) + 5;
    p->unk_190 = func_0209d368(100, 5) - 5;
    func_020ac39c((void *) p->sub, p->unk_18C, p->unk_190 + 4);
    func_020ac384(p->sub);
    func_0200467c(0x13);
}

void func_020a9fac(UnkStruct_020a9fac *self)
{
    unsigned int flag;

    if (self->unk_194 > func_0209d368(100, 3) + 2) {
        self->unk_18C += func_0209d368(100, 6) - 6;
        self->unk_190 += func_0209d368(100, 7) + 6;
    } else {
        self->unk_18C += func_0209d368(100, 8) + 2;
        self->unk_190 += func_0209d368(100, 9) - 2;
    }

    self->unk_194 -= 1;
    flag = (self->unk_194 <= 0) ? 1 : 0;

    if (flag > 0) {
        self->unk_18C = 0;
        self->unk_190 = 0;
    }

    func_020ac39c((char *) self + 0xc, self->unk_18C, self->unk_190 + 4);

    if (flag > 0) {
        int result;

        func_020abdc8((char *) self + 0xc);
        result = func_020aad3c((char *) self + 0x154);
        func_020abd68((char *) self + 0xc, (result == 0) ? 1 : 0, 0);
        func_020aae38((char *) self + 0x154);
        func_020a9fa4((UnkStruct_020a9fa4 *) self);
    }
}

void func_020a9fa4(UnkStruct_020a9fa4 *p)
{
    p->unk_08 = 2;
}

void func_020a9ebc(char *self)
{
    int r5, r0, cond;

    func_020aad9c(self + 0x154);
    cond = (func_020aad3c((void *) (self + 0x154)) == 0);
    func_020abd68((void *) (self + 0xc), cond, 1);
    func_020abd5c(self + 0xc, func_020aae88(self + 0x154));
    r5 = func_020aae78(self + 0x154);
    r0 = func_020abcc0(self + 0xc);
    if (r5 < 0) {
        goto L_neg;
    }
    if (r0 != 0xb) {
        goto L_not11;
    }
    func_020abdc0(self + 0xc);
    func_020aae30(self + 0x154);
    func_020a9e8c((UnkStruct_020a9e8c *) self);
    goto L_exit;
L_not11:
    func_020abc84(self + 0xc);
    goto L_exit;
L_neg:
    if (func_020aad8c(self + 0x154) == 0) {
        goto L_neg0;
    }
    if (func_020abccc(self + 0xc) != 0) {
        func_020abcb4(self + 0xc);
        goto L_exit;
    }
    if (func_020aad5c(self + 0x154) != 0) {
        func_020abca8(self + 0xc);
        goto L_exit;
    }
    func_020abc9c(self + 0xc);
    goto L_exit;
L_neg0:
    if (func_020aad7c(self + 0x154) != 0 && func_020abce4(self + 0xc) != 0) {
        func_020abc90(self + 0xc);
    }
L_exit:
    return;
}

void func_020a9e8c(UnkStruct_020a9e8c *object)
{
    object->unk_08 = 3;
    object->unk_198 = 1;
    object->unk_194 = func_0209d368(0x65, 2) + 2;
    func_0200467c(0x14);
}

void func_020a9e04(struct UnkStruct_020a9e04 *p)
{
    int flag;

    p->unk_198 = 0;
    p->unk_18C += func_0209d368(0x65, 3) + 11;
    p->unk_190 += func_0209d368(0x65, 4) - 11;
    p->unk_194--;
    flag = (p->unk_194 > 0) ? 0 : 1;
    func_020ac39c(p->sub, p->unk_18C, p->unk_190);
    if (flag) {
        func_020aae14(p->sub154);
        func_020aa154((unsigned int *) p);
    }
}

void func_020a9ddc(SELF *self)
{
    func_020ac46c(&self->unk_0C, func_020aae84(&self->unk_154));
    func_020ac4ec(&self->unk_0C);
}

void func_020a9dc8(void *arg, void *argument1)
{
    void *p = arg;
    func_020aa7e8((char *) p + 4, (void *) argument1);
    *(void **) p = (char *) p + 4;
}

void func_020a9db0(void *arg0, int argument1)
{
    void *r4;
    void *r0;

    r4 = arg0;
    r0 = (char *) arg0 + 0xc8;
    func_020aa2e4(r0, (int) argument1);
    r0 = (char *) r4 + 0xc8;
    *(void **) r4 = r0;
}

struct UnkStruct_020a9d88 *func_020a9d88(struct UnkStruct_020a9d88 *param)
{
    param->unk_00 = 0;
    func_020aa79c(&param->a);
    func_020aa28c(&param->b);
    param->unk_264 = 0;
    return param;
}

void *func_020a9d70(void *p)
{
    func_020aa25c((unsigned char *) p + 0xC8);
    func_020aa770((unsigned char *) p + 4);
    return p;
}

void func_020a9d38(UnkStruct_020a9d38_2 *self)
{
    if (self->ptr != 0) {
        self->ptr->vtable->fn2(self->ptr);
        if (self->ptr->vtable->fn4(self->ptr)) {
            self->ptr = 0;
            self->flag = 1;
        }
    } else {
        self->flag = 0;
    }
}

void func_020a9d24(void *ptr)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ptr)) != 0) {
        func_020aa7f4(condition_value0);
    }
}

int func_020a9d14(void *param)
{
    if (*(int *) param == 0) {
        return 1;
    }
    return 0;
}

int func_020a9cf8(UnkStruct_020a9cf8 **param)
{
    UnkStruct_020a9cf8 *obj;
    int result = 0;
    obj = *param;
    if (obj) {
        result = obj->vtable->unk_14(obj);
    }
    return result;
}

void func_020a9ce0(void **pp)
{
    void *p = *pp;
    if (p != 0) {
        Handler *handlers = *(Handler **) p;
        handlers[3](p);
    }
}
