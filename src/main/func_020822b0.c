/* func_020822b0 @ 0x020822b0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cd424[];

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
