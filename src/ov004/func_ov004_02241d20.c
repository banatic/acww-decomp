/* func_ov004_02241d20 @ 0x02241d20, 0x168 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02241ba8(void *self);
extern void func_020eaca0(int *v, void *p, void *q);
extern void func_ov004_02244fb8(int *v, int s);
extern void func_020ea838(int *v);
extern int func_020ea90c(int *a, int *b);
extern int func_020ea990(void *a, void *b);
extern const short data_02139d9c[];
extern int func_0200322c(void *a, void *b);
extern void func_020e8870(short *s, int a, int m);
extern int FX_MulFunc(int a, int b);
extern void func_ov004_02244f20(void *self);
extern void func_ov004_02244be0(void *self, int k);
extern void func_020550e4(void *p, int k);
extern int func_ov004_02244c20(void *self);
extern int func_020644cc(int k);

void func_ov004_02241d20(void *self, void *arg)
{
    int a, b;
    short s;
    int v1[3], v2[3];
    short *cnt = (short *) ((char *) self + 0x98);
    int *m = (int *) ((char *) self + 0x2c8);
    int t;

    a = func_ov004_02241ba8(self);
    s = *(short *) ((char *) self + 0x192);
    func_020eaca0(v1, arg, (char *) self + 0x2c8);
    func_ov004_02244fb8(v2, s);
    func_020ea838(v2);
    func_020ea838(v1);
    b = func_020ea90c(v2, v1);
    if (*((unsigned char *) arg + 0x14) != 0 && b > 0) {
        if (func_020ea990(m, arg) < 0x1800) {
            if (b > data_02139d9c[1]) {
                *cnt = (short) (*cnt + 1);
            }
        } else if (func_020ea990(m, arg) < 0x2800 && a == 0) {
            func_020e8870(&s, func_0200322c(arg, m), 0xaaa);
            *(short *) ((char *) self + 0x192) = s;
        }
    }
    if (*cnt > 0) {
        t = *cnt << 12;
        m[1] = FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
        if (m[1] < 3) {
            m[1] = 3;
            *cnt = 0;
        } else {
            *cnt = (short) (*cnt + 1);
        }
        func_ov004_02244f20(self);
        func_ov004_02244be0(self, 1);
    } else {
        func_ov004_02244be0(self, 0);
        if ((((unsigned int) *(int *) ((char *) self + 0x154) << 4) >> 16) != 0) {
            func_020550e4((char *) self + 0xb0, 0);
        }
    }
    if (func_ov004_02244c20(self) != 0 && *cnt == 0) {
        *(int *) ((char *) self + 0x174) = 0x14 * (func_020644cc(0xa) + 3);
        *(short *) ((char *) self + 0x172) = 0x19;
    }
}
