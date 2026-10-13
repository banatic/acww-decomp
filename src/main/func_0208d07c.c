/* func_0208d07c @ 0x0208d07c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used

void func_0208d07c(unsigned char *r0)
{
    unsigned int *r1;
    unsigned int r2;

    r1 = (unsigned int *) (r0 + 0xb4);
    if (*r1 != 0) {
        r1 = (unsigned int *) (r0 + 0xb0);
        r2 = *r1 + 1;
        r1 = (unsigned int *) (r0 + 0xb0);
        *r1 = r2;
        r0[0xa7] = 1;
    }
}
