/* func_02075c64 @ 0x02075c64, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern int func_02073d28(void *p, int a);
extern void func_02077b3c(int a, int b, int c);
extern int func_02073e30(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern void *data_020ccf94;

int func_02075c64(void)
{
    func_02073044();
    if (func_020ebf70() && func_02077a8c(1)) {
        void *p = data_020ccf94;
        func_02077b3c(func_02073d28(p, 4), 0, 7);
        return func_02073e30(p, func_02073d28(p, 4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
