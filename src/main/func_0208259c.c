/* func_0208259c @ 0x0208259c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020829ec(void *ctx, int a, int b);
extern int func_02082740(void *ctx, int a, int b);
extern char data_021d1d4c[];

int func_0208259c(int a, int b)
{
    int result;
    result = func_020829ec(&data_021d1d4c, a, b);
    if (result != 0) {
        return result;
    }
    return func_02082740(&data_021d1d4c, a, b);
}
