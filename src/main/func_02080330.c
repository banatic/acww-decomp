/* func_02080330 @ 0x02080330, 0xae bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_020803e0(void *);
extern int func_02080cf0(void *);
extern int func_020806f8(void *);
extern int func_02080684(void *, void *);

int func_02080330(void *a, void *b, void *c)
{
    int ea, eb;
    int va, vb;
    int fa, fb;

    if (func_02003704(func_0208150c(a)) == 0) {
        return 0;
    }
    if (func_02003704(func_0208150c(b)) == 0) {
        return 1;
    }

    ea = func_020803e0(a);
    eb = func_020803e0(b);
    if (ea > eb) {
        return 1;
    }
    if (ea < eb) {
        return 0;
    }

    va = func_02080cf0(a);
    vb = func_02080cf0(b);
    if (va != 0) {
        if (vb == 0) {
            return 1;
        }
    } else {
        if (vb != 0) {
            return 0;
        }
    }

    fa = func_020806f8(a);
    fb = func_020806f8(b);
    if (fa > fb) {
        return 1;
    }
    if (fa < fb) {
        return 0;
    }

    if (func_02080684(a, c) < func_02080684(b, c)) {
        return 1;
    }
    return 0;
}
