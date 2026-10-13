/* func_02079b7c @ 0x02079b7c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int arg);
extern int func_02079c74(signed char *a, int b, int c);
extern int func_02079ca4(signed char *a, int b);

int func_02079b7c(signed char *a, int b, int c)
{
    int ret = 0x80000000;
    int idx;
    if (func_0207cf74(b) && func_0207cf74(c)) {
        idx = func_02079c74(a, b, c);
        if (func_02079ca4(a, idx)) {
            ret = a[idx];
        }
    }
    return ret;
}
