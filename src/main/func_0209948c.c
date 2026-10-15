/* func_0209948c @ 0x0209948c, 0x1b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099a28(void *);
extern int func_02099640(void *);
extern int func_0209a850(int);
extern void func_0209b23c(void *);
extern int func_02099734(void *);
extern unsigned short *func_02098f48(int, int);
extern int func_02098e8c(int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern void func_02063414(unsigned short *, int, int, int, int, void *, int, int, int, int);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(unsigned short *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern int func_02098f0c(int, unsigned short *, int, int);
extern int func_020996ac(void *);
extern int OSi_DoUnlockByWord__main_0203cd2c(int, unsigned short *, int, int);

void func_0209948c(void *self)
{
    unsigned short w[6];
    int o[2][2];
    int a;
    int i;
    unsigned short *p;
    int t;
    unsigned int ok;

    if (func_02099a28(self) == 0) {
        return;
    }
    w[0] = 0xfff1;
    func_0209b23c((void *) func_0209a850((int) func_02099640(self)));
    a = func_02099734(self);
    p = func_02098f48(a, 0);

    for (i = 0; i < 0xf; p++, i++) {
        ok = 0;
        if (*p >= 0x155f && *p <= 0x1560) {
            ok = 1;
        }
        if (ok == 0) {
            continue;
        }
        if (func_02098e8c(a, i) != 2) {
            continue;
        }

        w[0] = 0xfff1;
        if (func_0204bcdc(p) != 0) {
            w[5] = 0x1560;
            t = func_0204bc64(p);
            ok = (t == func_0204bc64(&w[5])) ? 1 : 0;
        } else {
            if (*p == 0x1560) {
                ok = 1;
            } else {
                ok = 0;
            }
        }

        if (ok != 0) {
            func_02063414(&w[1], 0x1100, 0x44, 0, 0, self, 1, 10, 0, 1);
            w[0] = w[1];
            if (w[0] == 0xfff1) {
                func_02063ccc(o[0], 4, 0);
                func_020638d4(&w[2], o[0], 0, 0, 1, 1, 0);
                w[0] = w[2];
                func_02063cc8(o[0]);
            }
        } else {
            func_02063414(&w[3], 0x1144, 0x44, 0, 0, self, 1, 10, 0, 1);
            w[0] = w[3];
            if (w[0] == 0xfff1) {
                func_02063ccc(o[1], 3, 0);
                func_020638d4(&w[4], o[1], 0, 0, 1, 1, 0);
                w[0] = w[4];
                func_02063cc8(o[1]);
            }
        }

        func_02098f0c(a, &w[0], i, 0);
        if (w[0] != 0xfff1) {
            OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(self), &w[0], 0, 1);
        }
    }
}
