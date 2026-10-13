/* func_0208d12c @ 0x0208d12c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208d12c(void *arg0);

unsigned int func_0208d12c(void *arg0)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) ((char *) arg0 + 0xb4);
    value = *ptr;
    if (value == 0) {
        return 1;
    }
    return 0;
}
