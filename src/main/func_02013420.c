/* func_02013420 @ 0x02013420, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02013420(unsigned char *p)
{
    int i;
    p += 0x2c;
    for (i = 0; i < 29; i++) {
        if (((unsigned int) (p[2]) << 24) >> 28 == 0) {
            return i;
        }
        p += 3;
    }
    return 29;
}
