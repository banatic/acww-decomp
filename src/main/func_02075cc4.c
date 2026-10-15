/* func_02075cc4 @ 0x02075cc4, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020740dc(void);
extern unsigned int func_02073044(void);
extern __arm int func_020ebf70(void);
extern int func_02077a8c(void *);
extern int func_02073918(void *, int);
extern char *func_02073d28(void *, int);
extern void func_02077b3c(char *, int, int);
extern int func_02073e30(int, int, int, int, int, int, int, int, int, int);
extern void *data_020ccf94;

int func_02075cc4(void)
{
    void *ptr;
    void *g;
    char *tmp;
    int tmp2;

    ptr = func_020740dc();
    if (ptr == 0) {
        goto ret1;
    }
    func_02073044();
    if (func_020ebf70() == 0) {
        goto ret0;
    }
    if (func_02077a8c(ptr) == 0) {
        goto ret0;
    }
    g = data_020ccf94;
    func_02073918(g, 0);
    tmp = func_02073d28(g, 4);
    func_02077b3c(tmp, 0, 8);
    tmp[1] = 1;
    tmp2 = (int) func_02073d28(g, 4);
    return func_02073e30((int) g, tmp2, 2, (int) ptr, 0, 0, 0, 0, 0, 0);

ret0:
    return 0;
ret1:
    return 1;
}
