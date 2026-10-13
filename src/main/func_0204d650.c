/* func_0204d650 @ 0x0204d650, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
extern void *func_0207cec0(int *ptr, int value);
extern int func_0207ffdc(void *ptr, int *out1, int *out2);
extern int func_0204d698(int a, int b, int c, int d, int e);

int func_0204d650(int a, int b, int c, int d)
{
    int loc1, loc2;
    void *res;
    res = func_0207cec0(&data_021e5a2c, c);
    loc1 = 2;
    loc2 = 0;
    if (res != 0 && func_0207ffdc(res, &loc1, &loc2) != 0) {
        return func_0204d698(a, b, loc1, loc2, d);
    }
    return 0;
}
