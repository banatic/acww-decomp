/* field_actor_54: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022188d0 @ 0x022188d0, 0x48 bytes, Thumb
 * func_ov003_022188c8 @ 0x022188c8, 0x8 bytes, Thumb
 * func_ov003_022188ac @ 0x022188ac, 0x1c bytes, Thumb
 * func_ov003_02218890 @ 0x02218890, 0x1c bytes, Thumb
 * func_ov003_02218844 @ 0x02218844, 0x4c bytes, Thumb
 */

struct UnkStruct_022188c8 {
    int a;
    int b;
    unsigned short c;
};

struct UnkStruct_02218844 {
    int a;
    int b;
    short c;
};

struct Other {
    char pad_00[0xc];
    struct UnkStruct_02218844 sub;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02218918(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);
extern void func_020779b8(char *p, int a1, int a2);
extern void func_02077910(char *p, int a3);
extern void func_02077978(const unsigned char *record, unsigned int *out, unsigned int *extra);
extern int func_020778f8(int);
extern void func_020109a0(void *p, int b, int c, unsigned short d);

int func_ov003_022188d0(int a, int b, int c, int d, int e, short f)
{
    struct {
        int data[3];
    } loc1;
    struct {
        int data[5];
    } loc2;
    int ret;

    func_0200e92c(&loc1);
    func_0200e90c(&loc1, 0x38, e, f);
    func_ov003_02218918(&loc2, b, c, d);
    ret = func_0200e894(a, &loc1);
    func_0200e91c(&loc1);
    return ret;
}

void func_ov003_022188c8(struct UnkStruct_022188c8 *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = (unsigned short) c;
}

void func_ov003_022188ac(char *p, int a1, int a2, int a3)
{
    func_020779b8(p, a1, a2);
    func_02077910(p + 5, a3);
}

void func_ov003_02218890(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978((const unsigned char *) a1, (unsigned int *) a2, (unsigned int *) a3);
    *r4 = (short) func_020778f8(r5 + 5);
}

void func_ov003_02218844(char *self, struct Other *other, int previous)
{
    struct UnkStruct_02218844 *sub = &other->sub;
    int a, b;
    short c;

    func_020109a0(self, 0x37, 3, 0);
    a = sub->a;
    b = sub->b;
    c = sub->c;
    func_ov003_022188c8((struct UnkStruct_022188c8 *) (self + 0x7d4), a, b, c);
    func_ov003_022188ac((char *) (self + 0x8f0), a, b, c);
}
