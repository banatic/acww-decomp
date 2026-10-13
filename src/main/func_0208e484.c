/* func_0208e484 @ 0x0208e484, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a160(void *);

int func_0208e484(void *arg)
{
    int ret = 0;
    int cond;
    if (func_0208a160((char *) arg + 0xC) != 0) {
        if (((unsigned char *) arg)[0x49] != 0) {
            cond = func_0208a160((char *) arg + 0x2C);
        } else {
            cond = 1;
        }
        if (cond != 0) {
            ret = 1;
        }
    }
    return ret;
}
