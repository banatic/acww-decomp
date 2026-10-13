/* func_0207c6a4 @ 0x0207c6a4, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern void func_0209e474(Pair *pr);
extern int func_0208150c(void *p);
extern int func_02003704(int h);
extern void *func_0207f270(void *p);
extern int func_020794d8(void *q);
extern int func_02079544(void *q);
extern int func_0207a1c0(void *p, int i);
extern int func_020036e8(int h);
extern int func_020821d4(int v, Pair *pr);
extern void func_020794d4(void *q, int k);

void func_0207c6a4(char *p0)
{
    Pair pr;
    char *cur;
    int i;
    int h;
    void *q;
    int zero;

    cur = p0;
    pr.a = 0;
    pr.b = 0;
    func_0209e474(&pr);
    i = 0;
    zero = i;
    do {
        h = func_0208150c(cur);
        if (func_02003704(h) == 0) {
            goto next;
        }
        q = func_0207f270(cur);
        if (func_020794d8(q) != 2) {
            goto next;
        }
        if (func_02079544(q) != 0) {
            goto next;
        }
        if (func_0207a1c0(p0 + 0x3f7c, i) != ~zero) {
            goto next;
        }
        if (func_020821d4(func_020036e8(h), &pr) != 0) {
            goto next;
        }
        func_020794d4(q, 1);
    next:
        cur = cur + 0x7ec;
        i++;
    } while (i < 8);
}
