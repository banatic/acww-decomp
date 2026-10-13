/* func_02050c78 @ 0x02050c78, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02050c78(unsigned char *p, int v)
{
    p[0] = (unsigned char) v;
    p[1] = (unsigned char) (v >> 8);
    return 2;
}
