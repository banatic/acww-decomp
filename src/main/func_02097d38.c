/* func_02097d38 @ 0x02097d38, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02097d38(unsigned char *p, unsigned int mask)
{
    if ((p[3] & mask) == 0) {
        return 0;
    } else {
        return 1;
    }
}
