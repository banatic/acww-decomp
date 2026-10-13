/* func_02075b98 @ 0x02075b98, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern void func_02073918(void *, int);
extern int func_02073d28(void *, int);
extern void func_02077b3c(int, int, int);
extern int func_02073e30(void *, int, int, int, int, int, int, int, int, int);
extern void *data_020ccf94;

int func_02075b98(void)
{
    void *obj;
    int ret;

    func_02073044();
    if (func_020ebf70() != 0 && func_02077a8c(1) != 0) {
        obj = data_020ccf94;
        func_02073918(obj, 0);
        func_02077b3c(func_02073d28(obj, 4), 0, 9);
        ret = func_02073d28(obj, 4);
        return func_02073e30(obj, ret, 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
