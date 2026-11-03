/* field_actor_room_states_18: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229258 @ 0x02229258, 0x68 bytes, Thumb
 * func_ov004_0222920c @ 0x0222920c, 0x4a bytes, Thumb
 * func_ov004_02229204 @ 0x02229204, 0x8 bytes, Thumb
 * func_ov004_022291e8 @ 0x022291e8, 0x1c bytes, Thumb
 * func_ov004_022291cc @ 0x022291cc, 0x1c bytes, Thumb
 */

struct UnkStruct_02229258 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02229258_2 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02229258_3 {
    int a;
    int b;
    int c;
    int d;
};

typedef struct {
    char a[0xc];
    char b[0x14];
} UnkStruct_0222920c;

extern unsigned int func_0200e92c(struct UnkStruct_02229258_2 *c);
extern void func_0200e90c(struct UnkStruct_02229258_2 *c, int k, int a, int b);
extern void func_0200fa1c(struct UnkStruct_02229258 *out, void *self, struct UnkStruct_02229258 *in, unsigned short *p,
                          int *q);
extern void func_ov004_022292c0(struct UnkStruct_02229258_3 *o, int a, int c, short ang);
extern int func_0200e894(void *self, struct UnkStruct_02229258_2 *c);
extern int func_0200e91c(struct UnkStruct_02229258_2 *c);
extern int data_ov004_02247780;
extern void func_020779b8(char *p, int a1, int a2);
extern void func_02077910(char *p, int a3);
extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);
extern int func_020778f8(int);

int func_ov004_02229258(unsigned char *self, int a, int b)
{
    struct UnkStruct_02229258_2 ctx;
    struct UnkStruct_02229258_3 obj;
    struct UnkStruct_02229258 out;
    short ang;
    int r;

    func_0200e92c(&ctx);
    func_0200e90c(&ctx, 0x26, a, b);
    func_0200fa1c(&out, self, (struct UnkStruct_02229258 *) (self + 0x5c), (unsigned short *) (self + 0x8e),
                  &data_ov004_02247780);
    ang = (short) (*(short *) (self + 0x8e) + 0x4000);
    func_ov004_022292c0(&obj, out.a, out.c, ang);
    r = func_0200e894(self, &ctx);
    func_0200e91c(&ctx);
    return r;
}

int func_ov004_0222920c(void *self, int *b, int *c, short *d, int e, short g)
{
    UnkStruct_0222920c t;
    int r;
    func_0200e92c((struct UnkStruct_02229258_2 *) (&t));
    func_0200e90c((struct UnkStruct_02229258_2 *) (&t), 0x26, e, g);
    func_ov004_022292c0((struct UnkStruct_02229258_3 *) t.b, *b, *c, *d);
    r = func_0200e894(self, (struct UnkStruct_02229258_2 *) (&t));
    func_0200e91c((struct UnkStruct_02229258_2 *) (&t));
    return r;
}

void func_ov004_02229204(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}

void func_ov004_022291e8(char *p, int a1, int a2, int a3)
{
    func_020779b8(p, a1, a2);
    func_02077910(p + 5, a3);
}

void func_ov004_022291cc(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978((void *) (a1), (unsigned int *) (a2), (int) (a3));
    *r4 = (short) func_020778f8(r5 + 5);
}
