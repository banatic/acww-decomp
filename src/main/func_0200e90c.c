/* func_0200e90c @ 0x0200e90c, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200e90c(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
