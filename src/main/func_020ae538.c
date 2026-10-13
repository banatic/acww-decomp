/* func_020ae538 @ 0x020ae538, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020ae538(unsigned char *p, int index)
{
    int result;
    if ((signed char) p[4] != -1) {
        result = ((p[5] >> (index & 3)) & 1) != 0;
    } else {
        result = 0;
    }
    return result;
}
