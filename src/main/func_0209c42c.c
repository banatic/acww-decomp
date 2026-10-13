/* func_0209c42c @ 0x0209c42c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c38c(int);

void func_0209c42c(char *dst, int idx, char val)
{
    if (func_0209c38c(idx)) {
        dst[idx] = val;
    }
}
