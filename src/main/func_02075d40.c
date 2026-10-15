/* func_02075d40 @ 0x02075d40, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(void *);
extern void *data_020ccf94;
extern int func_02073d28(void *, int);
extern int func_0207332c(void *);
extern int func_02073e30(void *, int, int, void *, int, int, int, int, int, int);

int func_02075d40(void *arg)
{
    void *obj;
    int a, b;

    if ((func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c(arg) == 0) {
        goto fail;
    }

    obj = data_020ccf94;
    a = func_02073d28(obj, 4);
    b = func_0207332c(obj);

    return func_02073e30(obj, a, b, arg, 0, 0, 0, 0, 0, 0);

fail:
    return 0;
}
