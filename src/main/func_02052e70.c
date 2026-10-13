/* func_02052e70 @ 0x02052e70, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(int);
extern int func_02052fb4(int, int, int);

int func_02052e70(int a, int b, int c)
{
    int ret;

    ret = func_02052f3c(c);
    if (ret != 0) {
        return func_02052fb4(ret, a, b);
    }
    return 0;
}
