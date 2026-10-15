/* func_0200e7f8 @ 0x0200e7f8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *func_0200e86c(void *param, int index);

int func_0200e7f8(void *param)
{
    int index;
    int r2 = 0;
    int r0;

    if ((index = *(int *) ((char *) param + 0xC80)) >= 0) {
        r2 = func_0200e86c(param, index)[1];
    }

    r0 = *(int *) ((char *) param + 0x7FC) + 1;
    if (r0 > r2) {
        return r0;
    }
    return r2;
}
