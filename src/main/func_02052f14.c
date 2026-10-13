/* func_02052f14 @ 0x02052f14, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(int);
extern int func_0205307c(int, int, int, int);

int func_02052f14(int a, int b, int c, int d)
{
    int result;
    result = func_02052f3c(d);
    if (result) {
        return func_0205307c(result, a, b, c);
    } else {
        return 0;
    }
}
