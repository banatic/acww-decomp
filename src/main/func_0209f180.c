/* func_0209f180 @ 0x0209f180, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209fb3c(void *arg);

int func_0209f180(unsigned char *ptr)
{
    if (ptr[0] == 0x32) {
        if (func_0209fb3c(ptr + 0x173f8) != 0) {
            return 1;
        }
    }
    return 0;
}
