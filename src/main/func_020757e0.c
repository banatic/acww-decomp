/* func_020757e0 @ 0x020757e0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern void func_02073918(void *, int);
extern void *func_02073d28(void *, int);
extern void func_02077b3c(void *, int, int);
extern int func_02073e30(void *, void *, int, int, int, int, int, int, int, int);
extern void *data_020ccf94;

int func_020757e0(void)
{
    int ret;

    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(1) == 0) {
        goto fail;
    }
    {
        void *obj = data_020ccf94;
        func_02073918(obj, 0);
        func_02077b3c(func_02073d28(obj, 4), 0, 0x14);
        ret = func_02073e30(obj, func_02073d28(obj, 4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    goto exit;
fail:
    ret = 0;
exit:
    return ret;
}
