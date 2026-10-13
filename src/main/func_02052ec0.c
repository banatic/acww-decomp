/* func_02052ec0 @ 0x02052ec0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(int);
extern int func_02052fd0(int, int, int);

int func_02052ec0(int a, int b, int c)
{
    int ret = func_02052f3c(c);
    if (ret) {
        return func_02052fd0(ret, a, b);
    } else {
        return -1;
    }
}
