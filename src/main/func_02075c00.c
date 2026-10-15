/* func_02075c00 @ 0x02075c00, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(void *arg);
extern int func_02073d28(void *p, int param);
extern void func_02077b3c(int a, int b, int c);
extern int func_02073e30(void *p, int a, int b, void *arg, int c5, int c6, int c7, int c8, int c9, int c10);
extern void *data_020ccf94;

int func_02075c00(void *arg)
{
    void *p;
    int a;
    int b;

    func_02073044();
    if (func_020ebf70() && func_02077a8c(arg)) {
        p = data_020ccf94;
        a = func_02073d28(p, 4);
        func_02077b3c(a, 0, 11);
        b = func_02073d28(p, 4);
        return func_02073e30(p, b, 1, arg, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
