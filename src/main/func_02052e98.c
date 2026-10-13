/* func_02052e98 @ 0x02052e98, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(int a);
extern int func_02052fc0(int a, int b, int c, int d);

int func_02052e98(int p0, int p1, int p2, int p3)
{
    int result;
    result = func_02052f3c(p3);
    if (result != 0) {
        return func_02052fc0(result, p0, p1, p2);
    }
    return 0;
}
