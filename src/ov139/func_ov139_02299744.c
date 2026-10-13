/* func_ov139_02299744 @ 0x02299744, 0x2c bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov139_02299744(unsigned char *p)
{
    unsigned char b = p[0x9a3];
    if (b >= 0x14) {
        return p + 0x8d0;
    } else {
        p[0x9a3] = b + 1;
        return p + 0xcc + 0x6c * (p[0x9a3] - 1);
    }
}
