/* func_020b2a10 @ 0x020b2a10, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b2a10(unsigned int a, unsigned int b, unsigned int c);
unsigned int func_020b2a10(unsigned int a, unsigned int b, unsigned int c)
{
    return (a << 16) | (((c & 0xFF) << 8) | (b & 0xFF));
}
