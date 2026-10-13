/* func_ov094_0229b3f0 @ 0x0229b3f0, 0xd0 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b384(unsigned char *, int);
extern int func_ov094_0229b328(unsigned char *, int);
extern int func_ov094_0229b110(unsigned char *, int);
extern void func_ov094_0229b520(unsigned char *, int, int);
extern int func_ov094_0229b9a4(unsigned char *, int);
extern int func_ov094_0229b994(unsigned char *);
extern int func_ov094_0229b788(unsigned char *, unsigned char);
extern int func_02065ec0(int);
extern int func_ov094_0229b5c8(unsigned char *, int);
extern void func_ov094_0229b550(unsigned char *, int, int, int, int, int);
extern void func_ov094_0229b4f0(unsigned char *, int, int, int, int);
extern void func_ov094_0229b4c0(unsigned char *, int, int, int);

void func_ov094_0229b3f0(unsigned char *self, int p2, int mode, int v4, int v5)
{
    int a;
    int b;
    int tmp;

    a = v4 + func_ov094_0229b384(self, mode);
    b = v5 + func_ov094_0229b328(self, mode);

    if (a < -24) {
        return;
    }

    if (func_ov094_0229b110(self + 0x10, mode)) {
        func_ov094_0229b520(self, a, b);
    }

    if (func_ov094_0229b110(self + 8, mode)) {
        if (func_ov094_0229b9a4(self, mode)) {
            int t;

            t = func_ov094_0229b994(self);
            a += t;
            b += t;
        }

        if (func_ov094_0229b788(self, (unsigned char) mode) && func_02065ec0(p2) == 4) {
            tmp = 0xe;
        } else {
            tmp = func_ov094_0229b5c8(self, p2);
        }

        func_ov094_0229b550(self, a, b, tmp, p2, 0);
        func_ov094_0229b4f0(self, a, b, tmp, 0);

        if (func_ov094_0229b9a4(self, mode)) {
            func_ov094_0229b4c0(self, a, b, 0);
        }
    }
}
