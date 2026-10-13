/* func_020882cc @ 0x020882cc, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020882cc(unsigned char *addr, unsigned char val)
{
    addr[0xe] = (addr[0xe] & ~0x0f) | (val & 0x0f);
}
