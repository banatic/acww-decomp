/* func_ov096_0229daec @ 0x0229daec, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov098_022a31d8(int a);
extern int func_020b67d4(void);
extern int func_ov097_022a27c0(int a);

int func_ov096_0229daec(int arg)
{
    unsigned int first = (data_020e54a8 == 0);

    if (first > 0) {
        return func_ov098_022a31d8(arg);
    }

    if (func_020b67d4() != 0) {
        if (func_ov097_022a27c0(arg) == 0) {
            return 0;
        }
        return 1;
    }

    return 0;
}
