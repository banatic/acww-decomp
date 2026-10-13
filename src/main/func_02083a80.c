/* func_02083a80 @ 0x02083a80, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02083b00(unsigned int);

unsigned int func_02083a80(unsigned int *s, unsigned int index, unsigned int offset)
{
    unsigned int ret = 0;
    if (index < s[1]) {
        ret = func_02083b00(s[1]) + 8;
        ret += index * 4;
        ret += 1;
        ret += offset;
    }
    return ret;
}
