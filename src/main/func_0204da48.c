/* func_0204da48 @ 0x0204da48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80cc;
extern void func_0204da74(int a, int b);
extern void func_020e993c(int a, int b);

void func_0204da48(int param)
{
    if (data_021c80cc) {
        func_0204da74(data_021c80cc, param);
        func_020e993c(param, data_021c80cc);
        data_021c80cc = 0;
    }
}
