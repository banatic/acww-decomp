/* func_ov071_022790f0 @ 0x022790f0, 0x28 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov071_022790f0(unsigned short *r0, int r1);

unsigned short func_ov071_022790f0(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        if (value >= 0x3934 && value <= 0x3983) {
            result = 1;
        }
        return result;
    }
    return 0;
}
