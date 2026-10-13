/* func_ov096_0229e2c8 @ 0x0229e2c8, 0x32 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095f4c(int a, int b, int c, int d);
extern int func_02096150(int a, int b, int c, int d);
extern int func_02095f58(int a, int b, int c, int d);

int func_ov096_0229e2c8(int a, int b, int c, int d)
{
    switch (b) {
        case 5:
            return func_02095f4c(a, b, c, d);
        case 7:
        case 8:
            return (func_02096150(a, b, c, d) == 0) ? 1 : 0;
        default:
            return func_02095f58(a, b, c, d);
    }
}
