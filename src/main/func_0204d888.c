/* func_0204d888 @ 0x0204d888, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80c8;
extern int func_0204d8b0(void *p, int a, int b);

int func_0204d888(int a, int b)
{
    int result = 0;
    if (data_021c80c8 != 0) {
        if (func_0204d8b0(data_021c80c8, a, b) > 0) {
            result = 1;
        }
    }
    return result;
}
