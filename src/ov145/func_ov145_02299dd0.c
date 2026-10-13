/* func_ov145_02299dd0 @ 0x02299dd0, 0x38 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov145_02299dd0(unsigned char *param)
{
    volatile unsigned char *p = param;
    if (p[0xc4] >= 0x12) {
        return param + 0xa6c;
    }
    p[0xc4] = p[0xc4] + 1;
    return param + 0x340 + 108 * (p[0xc4] - 1);
}
