/* tile_requests_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02043568 @ 0x02043568, 0x36 bytes, Thumb
 * func_02043554 @ 0x02043554, 0x14 bytes, Thumb
 */

extern int func_0204482c(int a);
extern int func_02045b5c(int a);
extern int func_02043634(int a, int b, int c);
extern int func_02044858(int);
extern int func_020435fc(int, int);

int func_02043568(int param1, int param2)
{
    int arg2;

    if (func_0204482c(param1) == 0) {
        return -1;
    }
    if (func_02045b5c(param1) != 0) {
        arg2 = 18;
    } else {
        arg2 = 16;
    }
    return func_02043634(param1, arg2, param2);
}

int func_02043554(int a, int b)
{
    int c = b;
    return func_020435fc(func_02044858(a), c);
}
