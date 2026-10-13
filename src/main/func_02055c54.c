/* func_02055c54 @ 0x02055c54, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_02055c54(unsigned int unused, unsigned int a, unsigned int b)
{
    return (b & 0x8000ffff) | ((a >> 4) << 16);
}
