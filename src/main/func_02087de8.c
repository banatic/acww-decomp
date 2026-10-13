/* func_02087de8 @ 0x02087de8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02087de8(unsigned char *arg)
{
    unsigned int x = arg[8];
    unsigned int t = (x << 28) >> 30;
    t <<= 30;
    return (int) t >> 16;
}
