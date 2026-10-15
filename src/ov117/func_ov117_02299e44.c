/* func_ov117_02299e44 @ 0x02299e44, 0xa4 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_0204f3e4(int a, void *b, void *c, void *d, void *e, void *f, void *g, int h, int i);
extern void func_0204f800(int *out1, int *out2, int in1, int in2, int in3, int in4);
extern int func_020b3b50(void *p);
extern void func_020b3c58(int a, void *b, void *c, void *d, void *e);
extern void func_ov117_0229a2a4(void *self, int a, int b, int c, int d);

void func_ov117_02299e44(void *self)
{
    unsigned short v14;
    int v18, v1c, v20, v24, v28, v2c;
    int v30, v34, v38, v3c;
    int ret1, ret2;

    ret1 = func_0204e414();
    if (ret1 == 0) {
        return;
    }

    v14 = 0x500c;
    if (func_0204f3e4(ret1, &v20, &v24, &v28, &v2c, &v14, &v14, 2, 0) == 0) {
        return;
    }

    func_0204f800(&v18, &v1c, v20, v24, v28, v2c);

    v18 = v18 << 1;
    v1c = v1c << 1;
    v18 += 1;
    v1c += 1;

    ret2 = func_020b3b50(&v14);
    if (ret2 != 0) {
        func_020b3c58(ret2, &v30, &v34, &v38, &v3c);
        v18 += v30 >> 11;
        v1c += v34 >> 11;
    }

    func_ov117_0229a2a4(self, 0xf, v18, v1c, 0);
}
