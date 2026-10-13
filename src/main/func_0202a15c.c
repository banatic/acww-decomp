/* func_0202a15c @ 0x0202a15c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0202a15c(void *param);

unsigned short func_0202a15c(void *param)
{
    unsigned short result;
    unsigned short value;

    result = 0;
    value = *(unsigned short *) param;
    if (value >= 0x12e8 && value <= 0x131f) {
        result = 1;
    }
    return result;
}
