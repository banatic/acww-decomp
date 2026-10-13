/* func_02080c60 @ 0x02080c60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02080c60(unsigned short *out, unsigned char *base)
{
    unsigned char c;
    unsigned short val;
    val = 0x1380;
    *out = val;
    c = base[0x7da];
    if (c < 0x20) {
        if (c < 0x20) {
            val = (unsigned short) (c + 0x1380);
        }
        *out = val;
    }
}
