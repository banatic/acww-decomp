/* func_020c2898 @ 0x020c2898, 0x1a8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbbe0;
extern int func_0202ec58(void *p);
extern void *func_020984e8(void);
extern int func_020b65c4(void);
extern int func_020b65b8(void);
extern void func_0204f7e0(void *a, void *b);
extern int func_02078dd4(void *a, int b, int c, int d);
extern int func_02078e98(void *a, int b);
extern int func_0208602c(void);
extern int func_020860c4(int x);
extern int func_02087f30(int x);
extern void func_02087f40(int x, void *a);
extern void *func_0204e414(void);
extern int func_0204e08c(void *a, void *b, int c, int d);
extern int func_02099020(int a, int b);
extern int func_0202ea80(int a, int b);
extern void func_020c1b28(void *a, int b);
extern void func_020c26b4(void *a, int b);
extern void func_0203e334(void);

int func_020c2898(void *p)
{
    int a, b;
    void *q;

    if (func_0202ec58(p) == 0) {
        return 0;
    }

    data_021fbbe0 = p;
    *(int *) ((char *) p + 0x724) = -1;
    q = func_020984e8();

    if (func_020b65c4() == 0) {
        func_0204f7e0((char *) p + 0x5c, (char *) p + 0x5c);
        if (func_02078dd4((char *) p + 0x5c, 1, 0, 0)) {
            func_02078e98((char *) p + 0x5c, 0);
            *(int *) ((char *) p + 0x5c) += 0x2000;
            *(int *) ((char *) p + 0x64) += 0x2000;
        }

        a = func_0208602c();
        b = func_020860c4(a);
        if (func_02087f30(b) != 0) {
            if (func_020b65b8() == 0xb) {
                func_0204e08c(func_0204e414(), (char *) p + 0x5c, 0, 0);
                *(int *) ((char *) p + 0x64) -= 0x2000;
                func_020c1b28((char *) p + 0x658, 3);
                func_020c26b4(p, 5);
                *(char *) ((char *) p + 0x510) = 0;
            } else {
                func_020c1b28((char *) p + 0x658, 5);
                func_020c26b4(p, 1);
            }
        } else {
            if (func_02099020((int) q, 0x33) == 0) {
                if (func_02099020((int) q, 0x31) == 0) {
                    func_020c1b28((char *) p + 0x658, 0);
                } else {
                    func_020c1b28((char *) p + 0x658, 1);
                }
                func_020c26b4(p, 1);
            } else {
                if (func_0202ea80(0x29, 0) == 0) {
                    func_020c1b28((char *) p + 0x658, 2);
                } else {
                    func_020c1b28((char *) p + 0x658, 3);
                }
                func_020c26b4(p, 1);
            }
        }
    } else {
        if (func_020b65c4() == 0xb) {
            func_020c1b28((char *) p + 0x658, 3);
            func_020c26b4(p, 5);
            *(char *) ((char *) p + 0x510) = 0;
        } else if (func_020b65c4() == 0xc) {
            a = func_0208602c();
            b = func_020860c4(a);
            func_02087f40(b, (char *) p + 0x5c);
            func_020c1b28((char *) p + 0x658, 3);
            func_020c26b4(p, 5);
        } else if (func_020b65c4() == 0x2f) {
            *(char *) ((char *) p + 0x510) = 0;
            func_0203e334();
            func_020c26b4(p, 8);
        }
    }
    return 1;
}
