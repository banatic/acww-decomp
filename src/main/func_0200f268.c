/* func_0200f268 @ 0x0200f268, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200f268(char *base, int bit)
{
    *(unsigned int *) (base + 0x6ec) &= ~(1 << bit);
}
