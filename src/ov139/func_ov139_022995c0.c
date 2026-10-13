/* func_ov139_022995c0 @ 0x022995c0, 0x18 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

int func_ov139_022995c0(const unsigned short *p, unsigned short mask)
{
    return (p[0x4d0] & mask) != 0;
}
