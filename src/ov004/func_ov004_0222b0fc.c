/* func_ov004_0222b0fc @ 0x0222b0fc, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222b0fc {
    int a;
    int b;
    short c;
    unsigned char d;
    unsigned char e;
};
struct UnkStruct_0222b0fc_2 {
    int a;
    int b;
    int c;
};
extern int func_02073908(int a, int b);
extern void func_0200fa1c(struct UnkStruct_0222b0fc_2 *out, void *self, struct UnkStruct_0222b0fc_2 *in, unsigned short *p,
                          int *q);
extern void func_ov004_0222b1fc(void *dst, int a, int c, short sh, int k, int e);
extern void func_ov004_0222b1d8(void *dst, int a, int c, short sh, int k);
extern void func_02051e30(struct UnkStruct_0222b0fc_2 *in);
extern void func_020109fc(void *self, int a, int b, int c);
extern int data_020ccf94;
extern int data_ov004_02247780;
void func_ov004_0222b0fc(unsigned char *self, unsigned char *p)
{
    struct UnkStruct_0222b0fc *q;
    short sh;
    struct UnkStruct_0222b0fc_2 in, out;
    unsigned char *w;
    int a, b, k, g;

    q = (struct UnkStruct_0222b0fc *) (p + 0xc);
    b = q->b;
    a = *(int *) (p + 0xc);
    in.a = a;
    in.b = 0;
    in.c = b;
    sh = q->c;
    k = q->d;
    w = self + 0x7d4;
    g = data_020ccf94;
    if (func_02073908(g, *(int *) (self + 0x800)) != 0) {
        func_0200fa1c(&out, self, &in, (unsigned short *) &sh, &data_ov004_02247780);
        in.a = out.a;
        in.b = out.b;
        in.c = out.c;
    }
    func_ov004_0222b1fc(w, in.a, in.c, sh, k, q->e);
    func_ov004_0222b1d8(self + 0x8f0, in.a, in.c, sh, k);
    if (func_02073908(g, *(int *) (self + 0x800)) != 0) {
        func_02051e30(&in);
    }
    func_020109fc(self, 0x1a, 3, 0);
}
