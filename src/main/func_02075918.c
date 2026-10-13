/* func_02075918 @ 0x02075918, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern int func_02073d28(void *, int);
extern int func_02077b3c(int, int, int);
extern int func_02073e30(void *, int, int, int, int, int, int, int, int, int);
extern void *data_020ccf94;

int func_02075918(void)
{
    void *p;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }

    p = data_020ccf94;
    func_02077b3c(func_02073d28(p, 4), 0, 0x11);
    return func_02073e30(p, func_02073d28(p, 4), 1, 1, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}
