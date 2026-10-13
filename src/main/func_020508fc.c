/* func_020508fc @ 0x020508fc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02050920(int a, int b, unsigned short c, int d);

unsigned short func_020508fc(int a, int b, unsigned short c, int d)
{
    return (unsigned short) (((~(unsigned short) (func_02050920(a, b, c, d) - c)) & 0xFFFF) + 1);
}
