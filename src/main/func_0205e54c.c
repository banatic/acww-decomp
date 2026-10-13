/* func_0205e54c @ 0x0205e54c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0205e54c(char *base, int a, int b)
{
    char *p = base + (a << 3);
    p += (b << 2);
    return *(int *) (p + 0x190);
}
