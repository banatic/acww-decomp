/* func_02043568 @ 0x02043568, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204482c(int a, int b);
extern int func_02045b5c(int a);
extern int func_02043634(int a, int b, int c);

int func_02043568(int param1, int param2)
{
    int arg2;

    if (func_0204482c(param1, param2) == 0) {
        return -1;
    }
    if (func_02045b5c(param1) != 0) {
        arg2 = 18;
    } else {
        arg2 = 16;
    }
    return func_02043634(param1, arg2, param2);
}
