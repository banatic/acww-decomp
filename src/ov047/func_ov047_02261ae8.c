/* func_ov047_02261ae8 @ 0x02261ae8, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov047_02261ae8(void *r0, int r1);

unsigned short func_ov047_02261ae8(void *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *(unsigned short *) r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}
