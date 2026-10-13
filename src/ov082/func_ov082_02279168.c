/* func_ov082_02279168 @ 0x02279168, 0x28 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov082_02279168(unsigned short *r0, int r1);

unsigned short func_ov082_02279168(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;
    unsigned short limit_lo;
    unsigned short limit_hi;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        limit_lo = 0x12b0;
        limit_hi = 0x12e7;
        if (value >= limit_lo && value <= limit_hi) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}
