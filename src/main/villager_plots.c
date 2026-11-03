/* villager_plots: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207bd48 @ 0x0207bd48, 0x38 bytes, Thumb
 * func_0207bd28 @ 0x0207bd28, 0x20 bytes, Thumb
 */

extern int func_02081f80(short *p);
extern void func_02081f9c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char data_021d13a8[];

int func_0207bd48(short *a, int b, int c)
{
    int i = 0;
    int ret = -1;
    for (; i < b; i++) {
        if (func_02081f80(a)) {
            if (c == 0) {
                ret = i;
                break;
            } else {
                c--;
            }
        }
        a++;
    }
    return ret;
}

void func_0207bd28(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021d13a8), 0x1e, 2, (void (*)(void *)) func_02081f9c);
}
