/* func_ov047_02261c00 @ 0x02261c00, 0x20 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov047_02261c00(unsigned short *r0, int r1);

int func_ov047_02261c00(unsigned short *r0, int r1)
{
    int result;
    unsigned short val;

    if (r1 == 0) {
        result = 0;
        val = *r0;
        if (val >= 0x1549 && val <= 0x1549) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}
