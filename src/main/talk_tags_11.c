/* talk_tags_11: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a978 @ 0x0206a978, 0x20 bytes, Thumb
 * func_0206a8f4 @ 0x0206a8f4, 0x82 bytes, Thumb
 * func_0206a854 @ 0x0206a854, 0xa0 bytes, Thumb
 * func_0206a790 @ 0x0206a790, 0xc2 bytes, Thumb
 * func_0206a6ac @ 0x0206a6ac, 0xe4 bytes, Thumb
 * func_0206a694 @ 0x0206a694, 0x18 bytes, Thumb
 * func_0206a67c @ 0x0206a67c, 0x18 bytes, Thumb
 * func_0206a664 @ 0x0206a664, 0x18 bytes, Thumb
 * func_0206a64c @ 0x0206a64c, 0x18 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x08];
    int unk_30;
    char pad_34[0x04];
    char unk_38;
} UnkStruct_0206a8f4;

typedef struct UnkStruct_0206a854 {
    unsigned char pad_00[0x24];
    void *unk_24;
    unsigned char pad_28[0x8];
    int unk_30;
    unsigned char pad_34[0x4];
    void *unk_38;
} UnkStruct_0206a854;

struct func_0206a790_Self {
    unsigned char pad_00[0x24];
    unsigned char *unk_24;
    unsigned char pad_28[0x8];
    unsigned int unk_30;
    unsigned char pad_34[0x4];
    unsigned int unk_38;
};

typedef struct SelfType {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[8];
    int unk_30;
    char pad_34[4];
    int unk_38;
} SelfType;

typedef struct {
    char pad_00[0x24];
    int unk_24;
} FuncArg;

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} UnkStruct_0206a67c;

struct UnkStruct_0206a664 {
    char pad_00[0x24];
    unsigned int unk_24;
};

typedef struct UnkStruct_0206a64c {
    char pad_00[0x24];
    void *unk_24;
} UnkStruct_0206a64c;

extern void func_020a873c(void *param1, void *param2);
extern void func_020676c4(void *param1, unsigned char param2);
extern void *func_0206837c(void *);
extern void *func_020ab550(void *, int);
extern void func_020ab5e4(void *);
extern int func_020ab794(void *);
extern int func_020ab798(void *);
extern int func_020a85c4(void *, int, int, int, int);
extern void func_020ab4bc(void *, int);
extern void func_020a9dc8(void *, void *);
extern void func_020a9d24(void *);
extern int func_020a855c(void *ptr, int a, int b, int c, int d, int e, int f);
extern void func_020a93e8(void *self, int value);
extern int func_020a84e4(void *, int, int, int, int, int, int, int, int);
extern int func_020a8460(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_020ab4a8(void *object);

void func_0206a978(void *param0)
{
    unsigned char local;
    void *ptr;

    ptr = param0;
    func_020a873c((void *) ((unsigned int) ptr + 0x38), &local);
    func_020676c4(*(void **) ((unsigned int) ptr + 0x24), local);
}

void func_0206a8f4(UnkStruct_0206a8f4 *p)
{
    void *obj, *a, *b;
    int x, y, u, v, r;
    obj = func_0206837c(p->unk_24);
    a = func_020ab550(obj, 0);
    b = func_020ab550(obj, 1);
    func_020ab5e4(obj);
    x = func_020ab794(a);
    y = func_020ab798(a);
    u = func_020ab794(b);
    v = func_020ab798(b);
    r = func_020a85c4(&p->unk_38, x, y, u, v);
    func_020a93e8((void *) p, r);
    func_020ab4bc(obj, 2);
    func_020a9dc8(p->unk_24 + 0xb4, obj);
    func_020a9d24(p->unk_24 + 0xb4);
    p->unk_30 = 5;
}

void func_0206a854(UnkStruct_0206a854 *self)
{
    void *varA;
    void *varB, *varC;
    void *varD;
    int varE, varF, varG, varH, varI, varJ;
    int result1;

    varA = func_0206837c(self->unk_24);
    varB = func_020ab550(varA, 0);
    varC = func_020ab550(varA, 1);
    varD = func_020ab550(varA, 2);

    func_020ab5e4(varA);

    varE = func_020ab794(varB);
    varF = func_020ab798(varB);
    varG = func_020ab794(varC);
    varH = func_020ab798(varC);
    varI = func_020ab794(varD);
    varJ = func_020ab798(varD);

    result1 = func_020a855c(&self->unk_38, varE, varF, varG, varH, varI, varJ);
    func_020a93e8(self, result1);

    func_020ab4bc(varA, 3);

    func_020a9dc8((char *) self->unk_24 + 0xb4, varA);
    func_020a9d24((char *) self->unk_24 + 0xb4);

    self->unk_30 = 5;
}

void func_0206a790(struct func_0206a790_Self *self)
{
    void *n;
    void *a;
    void *b;
    void *c;
    void *d;
    int ax;
    int ay;
    int bx;
    int by;
    int cx;
    int cy;
    int dx;
    int dy;

    n = func_0206837c(self->unk_24);
    a = func_020ab550(n, 0);
    b = func_020ab550(n, 1);
    c = func_020ab550(n, 2);
    d = func_020ab550(n, 3);
    func_020ab5e4(n);

    ax = func_020ab794(a);
    ay = func_020ab798(a);
    bx = func_020ab794(b);
    by = func_020ab798(b);
    cx = func_020ab794(c);
    cy = func_020ab798(c);
    dx = func_020ab794(d);
    dy = func_020ab798(d);

    func_020a93e8(self, func_020a84e4(&self->unk_38, ax, ay, bx, by, cx, cy, dx, dy));
    func_020ab4bc(n, 4);
    func_020a9dc8(self->unk_24 + 0xb4, n);
    func_020a9d24(self->unk_24 + 0xb4);

    self->unk_30 = 5;
}

void func_0206a6ac(SelfType *self)
{
    void *list;
    void *e0, *e1, *e2, *e3, *e4;
    int a0, b0, a1, b1, a2, b2, a3, b3, a4, b4;
    int ret;

    list = func_0206837c(self->unk_24);
    e0 = func_020ab550(list, 0);
    e1 = func_020ab550(list, 1);
    e2 = func_020ab550(list, 2);
    e3 = func_020ab550(list, 3);
    e4 = func_020ab550(list, 4);
    func_020ab5e4(list);

    a0 = func_020ab794(e0);
    b0 = func_020ab798(e0);
    a1 = func_020ab794(e1);
    b1 = func_020ab798(e1);
    a2 = func_020ab794(e2);
    b2 = func_020ab798(e2);
    a3 = func_020ab794(e3);
    b3 = func_020ab798(e3);
    a4 = func_020ab794(e4);
    b4 = func_020ab798(e4);

    ret = func_020a8460(&self->unk_38, a0, b0, a1, b1, a2, b2, a3, b3, a4, b4);
    func_020a93e8(self, ret);
    func_020ab4bc(list, 5);
    func_020a9dc8((char *) self->unk_24 + 0xb4, list);
    func_020a9d24((char *) self->unk_24 + 0xb4);
    self->unk_30 = 5;
}

void func_0206a694(FuncArg *arg)
{
    func_0206a8f4((UnkStruct_0206a8f4 *) arg);
    func_020ab4a8((void *) (int) func_0206837c((void *) arg->unk_24));
}

void func_0206a67c(UnkStruct_0206a67c *arg)
{
    func_0206a854((UnkStruct_0206a854 *) arg);
    func_020ab4a8(func_0206837c(arg->unk_24));
}

void func_0206a664(struct UnkStruct_0206a664 *arg0)
{
    func_0206a790((struct func_0206a790_Self *) arg0);
    func_020ab4a8((void *) (unsigned int) func_0206837c((void *) arg0->unk_24));
}

void func_0206a64c(UnkStruct_0206a64c *s)
{
    func_0206a6ac((SelfType *) s);
    func_020ab4a8(func_0206837c(s->unk_24));
}
