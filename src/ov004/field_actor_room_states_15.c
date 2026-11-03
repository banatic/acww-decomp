/* field_actor_room_states_15: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229010 @ 0x02229010, 0x68 bytes, Thumb
 * func_ov004_02228fc4 @ 0x02228fc4, 0x4a bytes, Thumb
 * func_ov004_02228fbc @ 0x02228fbc, 0x8 bytes, Thumb
 * func_ov004_02228fa0 @ 0x02228fa0, 0x1c bytes, Thumb
 * func_ov004_02228f84 @ 0x02228f84, 0x1c bytes, Thumb
 */

struct UnkStruct_02229010 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02229010_2 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02229010_3 {
    int a;
    int b;
    int c;
    int d;
};

typedef struct {
    char a[0xc];
    char b[0x14];
} UnkStruct_02228fc4;

extern unsigned int func_0200e92c(struct UnkStruct_02229010_2 *c);
extern void func_0200e90c(struct UnkStruct_02229010_2 *c, int k, int a, int b);
extern void func_0200fa1c(struct UnkStruct_02229010 *out, void *self, struct UnkStruct_02229010 *in, unsigned short *p,
                          int *q);
extern void func_ov004_02229078(struct UnkStruct_02229010_3 *o, int a, int c, short ang);
extern int func_0200e894(void *self, struct UnkStruct_02229010_2 *c);
extern int func_0200e91c(struct UnkStruct_02229010_2 *c);
extern int data_ov004_02247780;
extern void func_020779b8(char *p, int a1, int a2);
extern void func_02077910(char *p, int a3);
extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);
extern int func_020778f8(int);

int func_ov004_02229010(unsigned char *self, int a, int b)
{
    struct UnkStruct_02229010_2 ctx;
    struct UnkStruct_02229010_3 obj;
    struct UnkStruct_02229010 out;
    short ang;
    int r;

    func_0200e92c(&ctx);
    func_0200e90c(&ctx, 0x27, a, b);
    func_0200fa1c(&out, self, (struct UnkStruct_02229010 *) (self + 0x5c), (unsigned short *) (self + 0x8e),
                  &data_ov004_02247780);
    ang = (short) (*(short *) (self + 0x8e) - 0x4000);
    func_ov004_02229078(&obj, out.a, out.c, ang);
    r = func_0200e894(self, &ctx);
    func_0200e91c(&ctx);
    return r;
}

int func_ov004_02228fc4(void *self, int *b, int *c, short *d, int e, short g)
{
    UnkStruct_02228fc4 t;
    int r;
    func_0200e92c((struct UnkStruct_02229010_2 *) (&t));
    func_0200e90c((struct UnkStruct_02229010_2 *) (&t), 0x27, e, g);
    func_ov004_02229078((struct UnkStruct_02229010_3 *) t.b, *b, *c, *d);
    r = func_0200e894(self, (struct UnkStruct_02229010_2 *) (&t));
    func_0200e91c((struct UnkStruct_02229010_2 *) (&t));
    return r;
}

void func_ov004_02228fbc(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}

void func_ov004_02228fa0(char *p, int a1, int a2, int a3)
{
    func_020779b8(p, a1, a2);
    func_02077910(p + 5, a3);
}

void func_ov004_02228f84(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978((void *) (a1), (unsigned int *) (a2), (int) (a3));
    *r4 = (short) func_020778f8(r5 + 5);
}
