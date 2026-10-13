/* func_020997e0 @ 0x020997e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020997e0(unsigned char *base, int value)
{
    base[0x243d] = (base[0x243d] & ~7) | (value & 7);
}
