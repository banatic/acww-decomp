/* func_ov004_02229678 @ 0x02229678, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02229678 {
    int a;
    int b;
    short c;
    unsigned char d;
};
struct UnkStruct_02229678_2 {
    int a;
    int b;
    int c;
};
extern void func_0200fa1c(struct UnkStruct_02229678_2 *out, void *self, struct UnkStruct_02229678_2 *in, unsigned short *p,
                          int *q);
extern void func_ov004_02229760(void *dst, int a, int c, short sh, int k);
extern void func_ov004_0222973c(void *dst, int a, int c, short s, int k);
extern int func_02073908(int a, int b);
extern void func_02051eb8(struct UnkStruct_02229678_2 *in);
extern void func_020109fc(void *self, int a, int b, int c);
extern short data_ov004_0224776c[];
extern int data_ov004_02254af8;
extern int data_020ccf94;
void func_ov004_02229678(unsigned char *self, unsigned char *p)
{
    struct UnkStruct_02229678 *q;
    short sh;
    struct UnkStruct_02229678_2 in, out;
    int a, b, x, k;
    short s;

    q = (struct UnkStruct_02229678 *) (p + 0xc);
    s = q->c;
    k = q->d;
    b = q->b;
    x = *(int *) (self + 0x60);
    a = q->a;
    in.a = a;
    in.b = x;
    in.c = b;
    sh = (short) (s + data_ov004_0224776c[k]);
    func_0200fa1c(&out, self, &in, (unsigned short *) &sh, &data_ov004_02254af8);
    func_ov004_02229760(self + 0x7d4, out.a, out.c, sh, k);
    func_ov004_0222973c(self + 0x8f0, in.a, in.c, s, k);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02051eb8(&in);
    }
    func_020109fc(self, 0x1a, 3, 0);
}
