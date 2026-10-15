/* func_ov096_0229e2c8 @ 0x0229e2c8, 0x32 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095f4c(void);
extern int func_02096150(void);
extern int func_02095f58(void);

int func_ov096_0229e2c8(int a, int b)
{
    switch (b) {
        case 5:
            return func_02095f4c();
        case 7:
        case 8:
            return (func_02096150() == 0) ? 1 : 0;
        default:
            return func_02095f58();
    }
}
