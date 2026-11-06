/* field_actor_25: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022122ac @ 0x022122ac, 0x4e bytes, Thumb
 * func_ov003_022122a0 @ 0x022122a0, 0xc bytes, Thumb
 * func_ov003_0221228c @ 0x0221228c, 0x14 bytes, Thumb
 * func_ov003_02212270 @ 0x02212270, 0x1a bytes, Thumb
 * func_ov003_0221220c @ 0x0221220c, 0x64 bytes, Thumb
 */

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    char data[12];
} UnkStruct_022122ac;

typedef struct {
    char data[16];
} Result;

extern unsigned int func_0200e92c(UnkStruct_022122ac *);
extern void func_0200e90c(UnkStruct_022122ac *, int, void *, short);
extern void func_ov003_022122fc(Result *, Pair *, void *);
extern int func_0200e894(void *, UnkStruct_022122ac *);
extern int func_0200e91c(UnkStruct_022122ac *);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(void *, int);

int func_ov003_022122ac(void *a, void *b, Pair *c, void *d, short e)
{
    Pair pair;
    UnkStruct_022122ac obj;
    Result result;
    int ret;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x5d, d, e);

    pair.x = c->x;
    pair.y = c->y;

    func_ov003_022122fc(&result, &pair, b);

    ret = func_0200e894(a, &obj);
    func_0200e91c(&obj);

    return ret;
}

void func_ov003_022122a0(unsigned char *r0, unsigned int *r1, unsigned char r2)
{
    r0[0] = (unsigned char) r1[0];
    r0[1] = (unsigned char) r1[1];
    r0[2] = r2;
}

void func_ov003_0221228c(unsigned char *out, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
}

void func_ov003_02212270(unsigned char *src, unsigned char *out1, unsigned char *out2, unsigned char *out3,
                         unsigned char *out4)
{
    *out1 = src[0];
    *out2 = src[1];
    *out3 = src[2];
    *out4 = src[3];
}

void func_ov003_0221220c(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char c = p[2];
    int b0 = p[0];
    int b1 = p[1];
    int loc[2];

    loc[0] = b0;
    loc[1] = b1;
    func_ov003_022122a0((unsigned char *) ((char *) self + 0x7d4), (unsigned int *) loc, c);
    func_ov003_0221228c((unsigned char *) ((char *) self + 0x8f0), c, (unsigned char) b0, (unsigned char) b1,
                        ((unsigned char *) self)[0x16c]);
    func_020109a0(self, 0x4c, 3, 0);
    if (c != 0) {
        func_0200f27c(self, 0x1c);
    }
}
