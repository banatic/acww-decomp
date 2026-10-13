/* func_0204d9d8 @ 0x0204d9d8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80c8;
extern void *func_020e9948(int, int);
extern void func_0204da2c(void *);
extern int func_0204d960(void *, int);
extern void func_0204d9ac(int);

int func_0204d9d8(int arg)
{
    int ret = 0;
    if (data_021c80c8 == 0) {
        void *p = func_020e9948(arg, 0x20);
        data_021c80c8 = p;
        if (p != 0) {
            if (p != 0) {
                func_0204da2c(p);
            }
            if (func_0204d960(data_021c80c8, arg) != 0) {
                ret = 1;
            } else {
                func_0204d9ac(arg);
                data_021c80c8 = 0;
            }
        }
    }
    return ret;
}
