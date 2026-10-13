/* func_ov143_02299650 @ 0x02299650, 0x12 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

int func_ov143_02299650(unsigned short *base, unsigned short mask)
{
    if ((base[0x4c] & mask) == 0) {
        return 0;
    }
    return 1;
}
