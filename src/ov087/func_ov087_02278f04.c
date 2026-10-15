/* func_ov087_02278f04 @ 0x02278f04, 0x28 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov087_02278f04(unsigned short *r0, int r1);

int func_ov087_02278f04(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        if (value >= 0x1542 && value <= 0x1546) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}
