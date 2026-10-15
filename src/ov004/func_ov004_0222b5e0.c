/* func_ov004_0222b5e0 @ 0x0222b5e0, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222b6a0(void *p, int k);
extern void func_ov004_0222b69c(void *p, int k);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void func_0200fa1c(int *v, void *self, void *p, short *b, int *a);
extern void func_02051e04(int *w);
extern void func_020109fc(void *self, int m, int a, int b);

void func_ov004_0222b5e0(void *self, void *msg, int previous)
{
    short b;
    int a;
    int w[3];
    int v[3];
    unsigned char k;
    int m;

    k = *((unsigned char *) msg + 0xc);
    func_ov004_0222b6a0((char *) self + 0x7d4, k);
    func_ov004_0222b69c((char *) self + 0x8f0, k);
    if (k != 0) {
        m = 0xc;
    } else {
        m = 0xf;
    }
    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        if (k == 0) {
            a = -0x2000;
        } else {
            a = 0x2000;
        }
        b = (short) (*(short *) ((char *) self + 0x8e) + 0x4000);
        func_0200fa1c(v, self, (char *) self + 0x5c, &b, &a);
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        func_02051e04(w);
        func_020109fc(self, m, 3, 0);
    } else {
        func_020109fc(self, m, 3, 0);
    }
}
