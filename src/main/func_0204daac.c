/* func_0204daac @ 0x0204daac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80cc;
extern int func_020e9958(int, int);
extern void func_0204dc88(void *);
extern int func_0204dafc(int, int, int);
extern void func_0204da48(int);

int func_0204daac(int a, int b)
{
    void *condition_value0;
    int ret = 0;
    if (data_021c80cc == 0) {
        data_021c80cc = func_020e9958(b, 0x24);
        if (data_021c80cc != 0) {
            if ((condition_value0 = (void *) (data_021c80cc)) != 0) {
                func_0204dc88(condition_value0);
            }
            if (func_0204dafc(data_021c80cc, a, b) != 0) {
                ret = data_021c80cc;
            } else {
                func_0204da48(b);
            }
        }
    }
    return ret;
}
