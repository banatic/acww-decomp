/* func_02081f80 @ 0x02081f80, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02081f80(const unsigned char *p)
{
    if (p[0] != 0xff && p[1] != 0xff) {
        return 1;
    } else {
        return 0;
    }
}
