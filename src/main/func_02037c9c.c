/* func_02037c9c @ 0x02037c9c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037ce0(unsigned short *base, unsigned short *ptr, unsigned int index);

int func_02037c9c(unsigned short *base, unsigned int a, unsigned int b)
{
    int ret = 0;
    if (a < 16 && b < 16) {
        ret = func_02037ce0(base, base + b, a);
    }
    return ret;
}
