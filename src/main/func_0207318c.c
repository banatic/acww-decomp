/* func_0207318c @ 0x0207318c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0207318c(char *base)
{
    unsigned short *p;
    int i;
    p = (unsigned short *) (base + 0x128);
    for (i = 2; i >= 0; i--) {
        *p++ = 0;
    }
}
