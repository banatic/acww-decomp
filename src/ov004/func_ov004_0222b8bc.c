/* func_ov004_0222b8bc @ 0x0222b8bc, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_0222b8bc {
    int a;
    int b;
    int c;
};
extern void func_ov004_0223a6ac(void *p);
extern void func_020109a0(void *self, int a, int b, int c);
extern int FX_MulFunc(int a, int b);
extern void func_ov004_0222b9c0(void *dst, int x, int z, short ang, int k);
extern void func_ov004_0222b9bc(void *dst, int b);
extern short FX_SinCosTable_[];
extern unsigned char data_020e54a8;
void func_ov004_0222b8bc(unsigned char *self, unsigned char *p)
{
    unsigned char *q, *w;
    struct UnkStruct_0222b8bc *s;
    int b0, t, A, c0, c1, d, B, x, z, u;
    short ang, ang2;

    q = p;
    q = q + 0xc;
    b0 = *(unsigned char *) (p + 0xc);
    u = (data_020e54a8 == 1) ? 1 : 0;
    if (u != 0) {
        func_ov004_0223a6ac(self + 0x5c);
    }
    func_020109a0(self, b0 != 0 ? 0xa : 9, 3, 0);
    ang = *(short *) (self + 0x8e);
    w = self + 0x7d4;
    d = 0x2000;
    if (b0 == 0) {
        d = ~0 * (unsigned) d;
    }
    t = 2 * (((unsigned short) ang) >> 4);
    c0 = FX_SinCosTable_[t];
    c1 = FX_SinCosTable_[t + 1];
    A = FX_MulFunc(c1, 0x1000) - FX_MulFunc(c0, d);
    B = FX_MulFunc(c0, 0x1000) + FX_MulFunc(c1, d);
    s = (struct UnkStruct_0222b8bc *) (self + 0x5c);
    x = s->a + B;
    z = s->c + A;
    if (b0 != 0) {
        ang2 = (short) (ang + 0x4000);
    } else {
        ang2 = (short) (ang - 0x4000);
    }
    func_ov004_0222b9c0(w, x, z, ang2, q[1]);
    func_ov004_0222b9bc(self + 0x8f0, b0);
}
