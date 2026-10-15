/* func_0200e828 @ 0x0200e828, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0200e86c(void *p, int index);

int func_0200e828(void *arg)
{
    int index;
    int r2 = 0;
    int r0;

    if ((index = *(int *) ((char *) arg + 0xC80)) >= 0) {
        char *ret = (char *) func_0200e86c(arg, index);
        r2 = *(int *) (ret + 4);
    }
    r0 = *(int *) ((char *) arg + 0x7FC);
    if (r0 <= r2) {
        r0 = r2;
    }
    return r0;
}
