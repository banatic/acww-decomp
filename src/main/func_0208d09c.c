/* func_0208d09c @ 0x0208d09c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder for pool constant if any

void func_0208d09c(void *self)
{
    if (*(int *) ((char *) self + 0xb4) != 0) {
        *(int *) ((char *) self + 0xac) = *(int *) ((char *) self + 0xac) + 1;
        *(char *) ((char *) self + 0xa6) = 1;
    }
}
