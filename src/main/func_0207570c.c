/* func_0207570c @ 0x0207570c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern int func_02073918(void *, int);
extern int func_02073d28(void *, int);
extern void func_02077b3c(int, int, int);
extern int func_02073e30(void *, int, int, int, int, int, int, int, int, int);
extern void *data_020ccf94;

int func_0207570c(void)
{
    void *p;
    int v2;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }

    p = data_020ccf94;
    func_02073918(p, 0);
    func_02077b3c(func_02073d28(p, 4), 0, 23);
    v2 = func_02073d28(p, 4);
    return func_02073e30(p, v2, 1, 1, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}
