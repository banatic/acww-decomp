/* func_0200f290 @ 0x0200f290, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0200f290(unsigned int *ptr, int bit)
{
    unsigned int value = ptr[0x1BB];
    return (value & (1 << bit));
}
