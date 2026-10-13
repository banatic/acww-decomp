/* func_020aad5c @ 0x020aad5c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aad8c(void *param);

int func_020aad5c(void *param)
{
    int result;
    unsigned char *ptr;

    result = func_020aad8c(param);
    if (result != 0) {
        ptr = (unsigned char *) param + 0x30;
        if (*ptr != 0) {
            return 1;
        }
    }
    return 0;
}
