/* func_020760bc @ 0x020760bc, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;

extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(void *a);
extern void func_02073918(void *g, int k);
extern unsigned char *func_02073d28(void *g, int k);
extern void func_02077b3c(void *p, int a, int b);
extern int func_02073dd4(void *g, unsigned int i);
extern int func_02096284(int k);
extern int func_02073e30(void *g, unsigned char *p, int k, void *a, int c1, int c2, int c3, int c4, int c5, int c6);

int func_020760bc(void *a)
{
    void *g;
    unsigned int mask;
    unsigned int i;
    int b;
    unsigned char *p;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(a) == 0) {
        goto fail;
    }
    g = data_020ccf94;
    func_02073918(g, 0);
    p = func_02073d28(g, 4);
    func_02077b3c(p, 0, 0);
    mask = 0;
    for (i = mask; i < 4; i++) {
        if (func_02073dd4(g, i) != 0) {
            mask |= (unsigned char) (1 << i);
        }
    }
    mask = mask & 0xf;
    b = (unsigned char) mask;
    b = b | ((((unsigned char) func_02096284(0)) << 6) & 0xc0);
    p[1] = (unsigned char) b;
    g = data_020ccf94;
    return func_02073e30(g, func_02073d28(g, 4), 2, a, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}
