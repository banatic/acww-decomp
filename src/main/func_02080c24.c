/* func_02080c24 @ 0x02080c24, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02080c24(unsigned char *out, const unsigned short *in)
{
    unsigned int flag = 0;
    unsigned int value = *in;

    if (value >= 0x1380u && value <= 0x139fu) {
        flag = 1;
    }

    if (flag != 0) {
        if (value >= 0x1380u && value <= 0x139fu) {
            flag = value - 0x1380u;
        } else {
            flag = -1;
        }

        out[0x7da] = (unsigned char) flag;
    }
}
