/* func_0204d9ac @ 0x0204d9ac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80c8;
extern void func_0204d934(int a, int b);
extern void func_020e993c(int a, int b);

void func_0204d9ac(int param)
{
    if (data_021c80c8) {
        func_0204d934(data_021c80c8, param);
        func_020e993c(param, data_021c80c8);
        data_021c80c8 = 0;
    }
}
