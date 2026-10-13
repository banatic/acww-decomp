/* func_0208e930 @ 0x0208e930, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a160(void *ptr);

int func_0208e930(void *arg)
{
    if (func_0208a160((void *) ((char *) arg + 0x14)) != 0 && func_0208a160((void *) ((char *) arg + 0x28)) != 0) {
        return 1;
    }
    return 0;
}
