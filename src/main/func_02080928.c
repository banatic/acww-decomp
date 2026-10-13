/* func_02080928 @ 0x02080928, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *p);
extern int func_02003704(int h);
extern char *func_0204c7c0(void);
extern void *func_0207b3dc(void *p);
extern void *func_020984e8(void);
extern void *func_0207f294(void *p);
extern int func_0207f150(void *p);
extern char *func_02099640(void *a);
extern int func_0209aebc(char *m, int h);

int func_02080928(void *p0)
{
    int ok;
    void *e;
    void *a;
    char *m;

    if (func_02003704(func_0208150c(p0)) == 0) {
        goto zero;
    }
    e = func_0207b3dc(func_0204c7c0() + 0x9284);
    a = func_020984e8();
    ok = 0;
    if (e == func_0207f294(p0)) {
        goto ret;
    }
    if (func_0207f150(p0) != 3) {
        goto ret;
    }
    if (a == 0) {
        goto ret;
    }
    m = func_02099640(a);
    m = m + 0xa4;
    if (func_0209aebc(m, func_0208150c(p0)) != 0) {
        goto ret;
    }
    ok = 1;
ret:
    return ok;
zero:
    return 0;
}
