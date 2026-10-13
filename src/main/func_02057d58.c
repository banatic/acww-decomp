/* func_02057d58 @ 0x02057d58, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020599a8(int, int, int, int, int, int, int);
extern int data_021c9350;

int func_02057d58(int a, int b, int c, int d, int e, int f)
{
    int result = 0;
    if (data_021c9350) {
        result = func_020599a8(data_021c9350, a, b, c, d, e, f);
    }
    return result;
}
