/* func_020758ac @ 0x020758ac, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(void *);
extern void *data_020ccf94;
extern int func_02073918(void *, int);
extern int func_02073d28(void *, int);
extern void func_02077b3c(int, int, int);
extern int func_02073e30(void *, int, int, void *, int, int, int, int, int, int);

int func_020758ac(void *a0)
{
    void *o;

    if ((func_02073044(), func_020ebf70()) == 0) {
        goto fail;
    }
    if (func_02077a8c(a0) == 0) {
        goto fail;
    }
    o = data_020ccf94;
    func_02073918(o, 0);
    func_02077b3c(func_02073d28(o, 4), 0, 0x12);
    return func_02073e30(o, func_02073d28(o, 4), 1, a0, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}
