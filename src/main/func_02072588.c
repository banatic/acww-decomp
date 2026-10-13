/* func_02072588 @ 0x02072588, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_02072588(unsigned int *base, unsigned int index)
{
    return *(base + (index & 0xF) + 1);
}
