/* func_ov004_0222631c @ 0x0222631c, 0x110 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222631c {
    int a;
    int b;
    int c;
};
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02064558(short a);
extern int func_02073908(int a, int b);
extern void func_ov004_02226434(void *p, int a, int c);
extern void VEC_Add(struct UnkStruct_0222631c *dst, struct UnkStruct_0222631c *a, struct UnkStruct_0222631c *b);
extern void func_01ffd070(struct UnkStruct_0222631c *out, struct UnkStruct_0222631c *a, struct UnkStruct_0222631c *b);
extern void func_ov004_0222643c(void *dst, struct UnkStruct_0222631c t, int k);
extern void func_0201107c(void *self, void *p);
extern unsigned int *func_0200f27c(void *self, int a);
extern int data_020ccf94;
extern int data_ov004_02254ae8;
void func_ov004_0222631c(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222631c *q, *s;
    struct UnkStruct_0222631c t, v, out;
    unsigned char *w, *w2;

    q = (struct UnkStruct_0222631c *) (p + 0xc);
    w = self + 0x7d4;
    func_020109fc(self, 1, 0, 0);
    *(int *) (self + 0x2e0) = 0;
    v.a = 0;
    v.b = 0;
    v.c = 0;
    w2 = self + 0x8f0;
    switch (func_02064558(*(short *) (self + 0x8e))) {
        case 2:
            v.c = v.c + 0x6000;
            break;
        case 0:
            v.c = v.c - 0x6000;
            break;
        case 3:
            v.a = v.a + 0x6000;
            break;
        case 1:
            v.a = v.a - 0x6000;
            break;
    }
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        s = (struct UnkStruct_0222631c *) (self + 0x5c);
        t.a = s->a;
        t.b = s->b;
        t.c = s->c;
        func_ov004_02226434(w2, t.a, t.c);
        VEC_Add((struct UnkStruct_0222631c *) (self + 0x5c), &v, (struct UnkStruct_0222631c *) (self + 0x5c));
    } else {
        t.a = q->a;
        t.b = q->b;
        t.c = q->c;
        func_01ffd070(&out, &t, &v);
        s = (struct UnkStruct_0222631c *) (self + 0x5c);
        s->a = out.a;
        s->b = out.b;
        s->c = out.c;
    }
    func_ov004_0222643c(w, t, 0x400);
    func_0201107c(self, &data_ov004_02254ae8);
    func_0200f27c(self, 5);
}
