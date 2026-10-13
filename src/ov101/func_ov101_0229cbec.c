/* func_ov101_0229cbec @ 0x0229cbec, 0x34 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void *arg0, int arg1);
extern int func_ov101_0229ce1c(void *arg0, int arg1);
extern int func_ov094_0229aaac(void *arg0, int arg1);

int func_ov101_0229cbec(void *arg0, int arg1)
{
    if (func_ov101_0229ce38(arg0, arg1) != 0) {
        int tmp = func_ov101_0229ce1c(arg0, arg1);
        return func_ov094_0229aaac((char *) arg0 + 0xf4, tmp);
    }
    return 0x0000fff1;
}
