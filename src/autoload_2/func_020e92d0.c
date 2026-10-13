/* func_020e92d0 @ 0x020e92d0, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020e92e8(unsigned int);

unsigned int func_020e92d0(unsigned int a, unsigned int b)
{
    unsigned int r;
    r = func_020e92e8(a);
    return (unsigned int) ((unsigned long long) b * r >> 32);
}
