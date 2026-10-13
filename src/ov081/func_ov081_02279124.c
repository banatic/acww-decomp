/* func_ov081_02279124 @ 0x02279124, 0x28 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov081_02279124(unsigned short *r0, int r1);

unsigned short func_ov081_02279124(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        if (value >= 0x12e8 && value <= 0x131f) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}
