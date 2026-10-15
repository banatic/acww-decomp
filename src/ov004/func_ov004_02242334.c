/* func_ov004_02242334 @ 0x02242334, 0x13c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223ee38(void);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern int func_020644cc(int k);
extern void func_ov004_02242a9c(void *self, int a, int b);
extern int func_ov004_02244c20(void *self);
extern unsigned char data_ov004_02259a24;
extern const short FX_SinCosTable_[];

void func_ov004_02242334(void *self)
{
    void *other;
    int *A, *B;
    char *C;
    int t, dist;
    int m;
    short *D;
    int v;
    unsigned char f;
    int q;

    other = func_ov004_0223ee38();
    A = (int *) ((char *) self + 0x2c8);
    B = (int *) ((char *) other + 0x2c8);
    C = (char *) self;
    C = (char *) ((int) C + 0x34);
    m = func_0200322c(B, A);
    D = (short *) ((char *) self + 0x168);
    v = *(int *) ((char *) self + 0x4c);
    if (data_ov004_02259a24 % 0xa == 0) {
        if (func_020644cc(0x64) > 0x32) {
            *((unsigned char *) self + 0x170) = 1;
        } else {
            *((unsigned char *) self + 0x170) = 0;
        }
    }
    f = *((unsigned char *) self + 0x170);
    if (f != 0 && v < 0x1554) {
        m = (short) (m + 0xb6);
        v += 0xb6;
    } else if (f == 0 && v > 0) {
        m = (short) (m - 0xb6);
        v -= 0xb6;
    } else if (f != 0) {
        *((unsigned char *) self + 0x170) = 0;
    } else {
        *((unsigned char *) self + 0x170) = 1;
    }
    dist = func_020ea990(C, B);
    t = ((int) (unsigned short) m >> 4) * 2;
    A[0] = B[0] + FX_MulFunc(FX_SinCosTable_[t], dist);
    A[2] = B[2] + FX_MulFunc(FX_SinCosTable_[t + 1], dist);
    *(short *) ((char *) other + 0x192) = (short) m;
    q = func_0200322c(A, B);
    *(short *) ((char *) self + 0x192) = (short) q;
    func_ov004_02242a9c(self, q, *D);
    *(int *) ((char *) self + 0x4c) = v;
    *D = (short) (*D + 1);
    if (func_ov004_02244c20(self) != 0) {
        *(short *) ((char *) self + 0x172) = 0x19;
        *D = 0;
    }
}
