/* func_02075848 @ 0x02075848, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern void *data_020ccf94;
extern int func_02073d28(void *, int);
extern void func_02077b3c(int, int, int);
extern int func_020740dc(void);
extern int func_02073e30(void *, int, int, int, int, int, int, int, int, int);

int func_02075848(void)
{
    void *o;
    if ((func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }
    o = data_020ccf94;
    func_02077b3c(func_02073d28(o, 4), 0, 0x13);
    func_020740dc();
    return func_02073e30(o, func_02073d28(o, 4), 1, 1, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}
