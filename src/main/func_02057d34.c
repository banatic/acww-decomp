/* func_02057d34 @ 0x02057d34, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9350;
extern int func_0205996c(int a, int b, unsigned int);

int func_02057d34(int param)
{
    int result = 0;
    int val = data_021c9350;
    if (val != 0) {
        result = func_0205996c(val, param, result);
    }
    return result;
}
