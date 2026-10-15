/* func_0202eac8 @ 0x0202eac8, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020160b4(void *);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, unsigned char *, int, unsigned char *, int, int);
extern void func_020ab5f8(void *);

void func_0202eac8(void *A, const unsigned char *p, int n, int x)
{
    void *t;
    unsigned char buf[2];
    int zero;
    int i;

    t = func_020160b4(A);
    func_020ab670(t, n, x);
    zero = 0;
    for (i = 0; i < n; i++) {
        buf[0] = *p;
        buf[1] = 0xff;
        func_020ab628(t, i, buf, zero, &buf[1], zero, zero);
        p++;
    }
    func_020ab5f8(t);
}
