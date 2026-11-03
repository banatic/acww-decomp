/* model_anim: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020565ec @ 0x020565ec, 0x24 bytes, Thumb
 * func_020565c8 @ 0x020565c8, 0x24 bytes, Thumb
 * func_020565b0 @ 0x020565b0, 0x18 bytes, Thumb
 * func_02056590 @ 0x02056590, 0x20 bytes, Thumb
 * func_02056578 @ 0x02056578, 0x18 bytes, Thumb
 * func_02056548 @ 0x02056548, 0x30 bytes, Thumb
 * func_0205650c @ 0x0205650c, 0x3c bytes, Thumb
 * func_020564d0 @ 0x020564d0, 0x3c bytes, Thumb
 * func_02056498 @ 0x02056498, 0x38 bytes, Thumb
 * func_02056478 @ 0x02056478, 0x1e bytes, Thumb
 * func_02056440 @ 0x02056440, 0x36 bytes, Thumb
 * func_02056424 @ 0x02056424, 0x1a bytes, Thumb
 * func_020563ec @ 0x020563ec, 0x36 bytes, Thumb
 * func_020563dc @ 0x020563dc, 0x10 bytes, Thumb
 * func_020563cc @ 0x020563cc, 0x10 bytes, Thumb
 */

typedef struct {
    volatile unsigned int unk_00;
    unsigned int unk_04;
    volatile unsigned int unk_08;
    volatile unsigned int unk_0C;
    volatile unsigned int unk_10;
    unsigned int unk_14;
    volatile unsigned int unk_18;
    volatile unsigned int unk_1C;
} UnkStruct_020565c8;

struct UnkStruct_020565b0 {
    void *unk_00;
};

typedef struct {
    char pad_00[0x18];
    void *unk_18;
    int unk_1C;
} UnkStruct_0205650c;

typedef struct {
    unsigned char pad_00[0x18];
    void *unk_18;
    void *unk_1C;
} UnkStruct_020564d0;

typedef struct {
    char pad_00[0x18];
    unsigned int *unk_18;
    unsigned int *unk_1C;
} UnkStruct_02056498;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
} UnkStruct_02056498_2;

struct UnkStruct_020563cc {
    char pad_00[0x18];
    int unk_18;
};

extern unsigned char data_020dd154[];
extern unsigned char data_020dd184[];
extern void func_02057054(void *);
extern void func_020edb3c(void *);
extern int NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(int a, int b);
extern int func_020e9948(int a, int b);
extern int data_021fbe94;
extern char data_020dd148;
extern char data_020dd144[];
extern void func_02056fcc(UnkStruct_02056498 *a, unsigned int b, int c, void *d, unsigned int e);
extern void NNS_G3dAnmObjInit(unsigned int *a, UnkStruct_02056498_2 *b, unsigned int *c, void *d);
extern void NNS_G3dRenderObjAddAnmObj(void *a, void *b);
extern void NNS_G3dRenderObjRemoveAnmObj(int param1, int param2);

void func_020563dc(void *a, void *b);
void func_020563cc(struct UnkStruct_020563cc *a, int b);

void func_020565ec(unsigned int *r0)
{
    unsigned int r1;
    unsigned int r2;

    r1 = (unsigned int) ((unsigned int *) data_020dd184);
    *r0 = r1;
    r2 = 0;
    *(r0 + 2) = r2;
    *(r0 + 3) = r2;
    r1 = 0x1000;
    *(r0 + 4) = r1;
    r1 = (unsigned int) ((unsigned int *) data_020dd154);
    *r0 = r1;
    *(r0 + 7) = r2;
    *(r0 + 6) = r2;
}

void func_020565c8(UnkStruct_020565c8 *p)
{
    p->unk_00 = (unsigned int) data_020dd184;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0x1000;
    p->unk_00 = (unsigned int) data_020dd154;
    p->unk_1C = 0;
    p->unk_18 = 0;
}

struct UnkStruct_020565b0 *func_020565b0(struct UnkStruct_020565b0 *obj)
{
    obj->unk_00 = ((char *) data_020dd154);
    func_02057054((void *) obj);
    return obj;
}

void *func_02056590(void *self)
{
    *(void **) self = ((char *) data_020dd154);
    func_02057054(self);
    func_020edb3c(self);
    return self;
}

void *func_02056578(void *arg)
{
    *(unsigned int *) arg = (unsigned int) ((unsigned int *) data_020dd154);
    func_02057054(arg);
    return arg;
}

int func_02056548(int a, int b, int c)
{
    int ret;
    if (a == 0) {
        return 0;
    }
    ret = NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(b, a);
    if (c == 0) {
        c = data_021fbe94;
    }
    return func_020e9948(c, ret);
}

int func_0205650c(UnkStruct_0205650c *ctx, int arg, int argument2)
{
    if (ctx->unk_18 != 0 || ctx->unk_1C != 0) {
        return 0;
    }
    ctx->unk_18 = (void *) func_02056548(arg, (int) (&data_020dd148), (int) argument2);
    ctx->unk_1C = arg;
    if (ctx->unk_18 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_020564d0(UnkStruct_020564d0 *param0, void *param1, int argument2)
{
    if (param0->unk_18 || param0->unk_1C) {
        return 0;
    }
    param0->unk_18 = (void *) func_02056548((int) param1, (int) data_020dd144, (int) argument2);
    param0->unk_1C = param1;
    return param0->unk_18 ? 1 : 0;
}

void func_02056498(UnkStruct_02056498 *a, UnkStruct_02056498_2 *b, void *c, int d, void *e, unsigned short f)
{
    func_02056fcc(a, b->unk_04, d, e, f);
    NNS_G3dAnmObjInit(a->unk_18, b, a->unk_1C, c);
    *a->unk_18 = f << 12;
}

void func_02056478(int a, int b, int c, int d, unsigned short e)
{
    func_02056498((UnkStruct_02056498 *) a, (UnkStruct_02056498_2 *) b, 0, c, (void *) d, e);
}

void func_02056440(int p0, int p1, int p2, int p3, int p4, unsigned short p5)
{
    func_020563cc((struct UnkStruct_020563cc *) p0, p1);
    func_02056498((UnkStruct_02056498 *) p0, (UnkStruct_02056498_2 *) p2, 0, p3, (void *) p4, p5);
    func_020563dc((void *) p0, (void *) p1);
}

void func_02056424(int a, int b, int c, int d, int e, unsigned short f)
{
    func_02056498((UnkStruct_02056498 *) a, (UnkStruct_02056498_2 *) b, (void *) c, d, (void *) e, f);
}

void func_020563ec(int a, int b, int c, int d, unsigned char e, int f, unsigned short g)
{
    func_020563cc((struct UnkStruct_020563cc *) a, b);
    func_02056498((UnkStruct_02056498 *) a, (UnkStruct_02056498_2 *) c, (void *) d, (unsigned char) e, (void *) f, g);
    func_020563dc((void *) a, (void *) b);
}

void func_020563dc(void *a, void *b)
{
    void *r2 = a;
    void *r0 = b;
    void *r1 = *(void **) ((char *) r2 + 0x18);
    NNS_G3dRenderObjAddAnmObj(r0, r1);
}

void func_020563cc(struct UnkStruct_020563cc *a, int b)
{
    NNS_G3dRenderObjRemoveAnmObj(b, a->unk_18);
}
