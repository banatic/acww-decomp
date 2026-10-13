/* func_ov050_022637c0 @ 0x022637c0, 0x28 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov050_022637c0(unsigned short *r0, int r1);

unsigned short func_ov050_022637c0(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}
