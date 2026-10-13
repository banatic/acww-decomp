/* func_0203734c @ 0x0203734c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203734c(void *self);

int func_0203734c(void *self)
{
    if (*(int *) ((char *) self + 0xc) != *(int *) self) {
        return 1;
    }
    return 0;
}
