/* room_cells: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02052ec0 @ 0x02052ec0, 0x28 bytes, Thumb
 * func_02052e98 @ 0x02052e98, 0x26 bytes, Thumb
 * func_02052e70 @ 0x02052e70, 0x26 bytes, Thumb
 */

extern int func_02052f3c(int);
extern int func_02052fd0(int, int, int);
extern int func_02052fc0(int a, int b, int c, int d);
extern int func_02052fb4(int, int, int);

int func_02052ec0(int a, int b, int c)
{
    int ret = func_02052f3c(c);
    if (ret) {
        return func_02052fd0(ret, a, b);
    } else {
        return -1;
    }
}

int func_02052e98(int p0, int p1, int p2, int p3)
{
    int result;
    result = func_02052f3c(p3);
    if (result != 0) {
        return func_02052fc0(result, p0, p1, p2);
    }
    return 0;
}

int func_02052e70(int a, int b, int c)
{
    int ret;

    ret = func_02052f3c(c);
    if (ret != 0) {
        return func_02052fb4(ret, a, b);
    }
    return 0;
}
