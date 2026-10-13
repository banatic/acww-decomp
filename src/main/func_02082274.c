/* func_02082274 @ 0x02082274, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_020cd494[];

unsigned int func_02082274(unsigned int a, unsigned int b)
{
    const unsigned char *p = data_020cd494;
    unsigned int ret = 0;
    unsigned char i = 0;

    while (i < 12u) {
        if (a < p[0] || (a == p[0] && b <= p[1])) {
            ret = i;
            break;
        }
        p += 2;
        i++;
    }

    return ret;
}
