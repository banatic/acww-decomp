/* func_0207cd84 @ 0x0207cd84, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

extern "C" {
extern char *func_0207cec0(void *, int);
extern void *func_0208150c(char *);
extern int func_02003704(void *);
extern int func_020807a8(char *, void *);
extern void func_020a8c1c(void *);
extern int func_02003618(void *, void *);
extern int func_020a87e0(void *, void *);
extern int func_02094f40(void *);
extern int func_0207ce70(void *, int);
extern int func_0207ce48(void *, void *, int);
}

struct A {
    char pad[0x20];
};

struct B {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void *v3();
    char pad[0x1c];
};

// Same layout as B; built and torn down by its out-of-line pair.
struct BBuf {
    void *vtbl;
    char pad[0x1c];
};

extern "C" char *func_0207cd84(void *p0, void *p1, int p2, void *p3)
{
    char *p;
    char *res;
    int n;
    int i;
    void *s;
    int len;
    int m;
    B *bp;

    p = func_0207cec0(p0, 0);
    A a;
    BBuf b;
    func_02094fd4(&a);
    func_02094f7c(&b);
    bp = (B *) &b;
    res = 0;
    n = func_0207ce70(p1, p2);
    if (n > 0 && n <= 6) {
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p)) != 0) {
                if (p3 == 0 || func_020807a8(p, p3) != 0) {
                    func_020a8c1c(&a);
                    func_02003618(func_0208150c(p), &a);
                    func_020a87e0(&b, &a);
                    s = bp->v3();
                    len = func_02094f40(&b);
                    m = func_0207ce70(s, len);
                    if (m == n) {
                        if (func_0207ce48(s, p1, m) != 0) {
                            res = p;
                            break;
                        }
                    }
                }
            }
            p += 0x7ec;
        }
    }
    func_02094f64(&b);
    func_02094fbc(&a);
    return res;
}
