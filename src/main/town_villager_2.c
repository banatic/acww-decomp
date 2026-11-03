/* town_villager_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02080c60 @ 0x02080c60, 0x24 bytes, Thumb
 * func_02080c24 @ 0x02080c24, 0x3c bytes, Thumb
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
