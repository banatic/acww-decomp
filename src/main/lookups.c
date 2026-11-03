/* lookups: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020822b0 @ 0x020822b0, 0x58 bytes, Thumb
 * func_02082274 @ 0x02082274, 0x3c bytes, Thumb
 * func_02082264 @ 0x02082264, 0x10 bytes, Thumb
 */

extern unsigned char data_020cd424[];
extern const unsigned char data_020cd494[];

unsigned char func_020822b0(unsigned char *p)
{
    unsigned char result = 0;

    switch (p[0]) {
        case 0:
        case 1:
        case 2:
            result = (unsigned char) (data_020cd424[p[0]] + p[1] - 1);
            break;
        case 3:
            result = (unsigned char) (data_020cd424[p[0]] + p[1]);
            break;
        case 4:
            if (p[1] < 12) {
                result = (unsigned char) (data_020cd424[p[0]] + p[1]);
            }
            break;
    }

    return result;
}

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

unsigned int func_02082264(unsigned char *arg0)
{
    unsigned char a;
    unsigned char b;

    a = arg0[0];
    b = arg0[1];
    return func_02082274((unsigned char) a, (unsigned char) b);
}
