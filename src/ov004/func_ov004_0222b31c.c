/* func_ov004_0222b31c @ 0x0222b31c, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222b31c {
    int a;
    int b;
    int c;
};
extern int func_02073908(int a, int b);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200fa1c(struct UnkStruct_0222b31c *out, void *self, struct UnkStruct_0222b31c *in, unsigned short *p,
                          int *q);
extern void func_ov004_0222b3e0(void *dst, int a, int c);
extern void func_ov004_0222b3dc(void *dst, int b);
extern void func_0200f328(void *self, int msg);
extern int data_020ccf94;
void func_ov004_0222b31c(unsigned char *self, unsigned char *p)
{
    unsigned char *w;
    short sh;
    int v;
    volatile struct UnkStruct_0222b31c r;
    struct UnkStruct_0222b31c out;
    int b, k;

    b = *(unsigned char *) (p + 0xc);
    k = b != 0 ? 0xb : 0xe;
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_020109a0(self, k, 3, 0);
    } else {
        func_020109a0(self, k, 0, 0);
    }
    w = self + 0x7d4;
    if (b == 0) {
        v = -0x2000;
    } else {
        v = 0x2000;
    }
    sh = (short) (*(short *) (self + 0x8e) + 0x4000);
    func_0200fa1c(&out, self, (struct UnkStruct_0222b31c *) (self + 0x5c), (unsigned short *) &sh, &v);
    r.a = out.a;
    r.b = out.b;
    r.c = out.c;
    func_ov004_0222b3e0(w, out.a, out.c);
    func_ov004_0222b3dc(self + 0x8f0, b);
    func_0200f328(self, 0x435);
}
