/* func_020c2f3c @ 0x020c2f3c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020c2f60(void *param);

int func_020c2f3c(void *param)
{
    int result;
    void *ptr;

    ptr = *(void **) ((char *) param + 0x98);
    if (ptr != 0) {
        result = func_020c2f60(param);
        if (result != 0) {
            return 1;
        }
    }
    return 0;
}
