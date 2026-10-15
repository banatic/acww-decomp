/* func_ov004_0222aea4 @ 0x0222aea4, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222aea4 {
    int a;
    int b;
    int c;
    unsigned char d;
};
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_0200f328(void *self, int a);
extern int func_02064558(short a);
extern void func_ov004_0222af58(void *dst, int b, int c, short ang, int d);
extern void func_ov004_0222af48(void *dst, int b0, int b, int c);
void func_ov004_0222aea4(unsigned char *self, unsigned char *p, int previous)
{
    struct UnkStruct_0222aea4 *q;
    unsigned char *w;
    int b0, b, c;
    short t, ang;
    q = (struct UnkStruct_0222aea4 *) (p + 0xc);
    b0 = *(unsigned char *) (p + 0xc);
    func_020109a0(self, b0 == 0 ? 8 : 7, 3, 0);
    func_0200f328(self, 0x4c5);
    w = self + 0x7d4;
    t = (short) (func_02064558(*(short *) (self + 0x8e)) << 14);
    b = q->b;
    c = q->c;
    if (b0 == 0) {
        ang = (short) (t + 0x4000);
    } else {
        ang = (short) (t - 0x4000);
    }
    func_ov004_0222af58(w, b, c, ang, q->d);
    func_ov004_0222af48(self + 0x8f0, b0, b, c);
}
