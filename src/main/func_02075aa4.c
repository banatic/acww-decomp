/* func_02075aa4 @ 0x02075aa4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_020ccf94;

extern unsigned int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(void *p);
extern unsigned char *func_02073d28(unsigned char *g, int k);
extern void func_02077b3c(unsigned char *t, int a, int b);
extern int func_02073e30(unsigned char *g, unsigned char *t, int k, void *p, int a, int b, int c, int d, int e, int f);

int func_02075aa4(int a, void *p1)
{
    unsigned char *g;
    unsigned char *t;

    if (p1 == 0) {
        goto one;
    }
    func_02073044();
    if (func_020ebf70() == 0) {
        goto zero;
    }
    if (func_02077a8c(p1) == 0) {
        goto zero;
    }
    g = data_020ccf94;
    t = func_02073d28(g, 4);
    func_02077b3c(t, 0, 0xe);
    t[1] = (unsigned char) a;
    return func_02073e30(g, func_02073d28(g, 4), 2, p1, 0, 0, 0, 0, 0, 0);
zero:
    return 0;
one:
    return 1;
}
