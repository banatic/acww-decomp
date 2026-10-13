/* func_0206426c @ 0x0206426c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

unsigned short func_0206426c(void)
{
    unsigned short x;

    x = (unsigned short) func_020644cc(0x7fff);
    x |= 0x8000;
    return x;
}
